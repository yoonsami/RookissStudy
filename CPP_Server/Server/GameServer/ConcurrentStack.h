#pragma once
#include <mutex>

//Lock-Based
template<typename T>
class LockStack
{
public:
	LockStack(){}
	LockStack(const LockStack&) = delete;
	LockStack& operator=(const LockStack&) = delete;

	void Push(T value)
	{
		lock_guard<mutex> lock(_mutex);
		_stack.push(std::move(value));
		_condVar.notify_one();
	}

	bool TryPop(T& value)
	{
		lock_guard<mutex> lock(_mutex);
		if (_stack.empty())
			return false;

		value = std::move(_stack.top());
		_stack.pop();
		return true;
	}
	
	/*bool Empty() 
	// Empty��� �Ǵ��ص� Pop�ϴ� ������ �ٸ� �����忡��
	�����͸� �߰��� �� �ֱ� ������ �����ϴ� empty�� ������ ����
	* 
	{
		lock_guard<mutex> lock(_mutex);
		return _stack.empty();
	}*/
	void WaitPop(T& value)
	{
		unique_lock<mutex> lock(_mutex);
		_condVar.wait(lock, [this] {/*Until*/return _stack.empty == false; });
		value = std::move(_stack.top());
		_stack.pop();
	}

private:
	stack<T> _stack;
	mutex _mutex;
	condition_variable _condVar;
};

//Lock-Free
/*template<typename T>
class LockFreeStack
{
	struct Node
	{
		Node(const T& value) : data(make_shared<T>(value)),next(nullptr)
		{}
		shared_ptr<T> data;
		shared_ptr<Node> next;
	};

public:
	void Push(const T& value)
	{
		//1) ��� ����
		//2) �� ����� next�� ����
		//3) ��带 �� ����
		shared_ptr<Node> node = make_shared<Node>(value);
		node->next = std::atomic_load(&_head);

		while (std::atomic_compare_exchange_weak(&_head, &node->next, node) == false)
		{
		}
	}

	shared_ptr<T> TryPop()
	{
		//1)Head �б� -> �б���� ���� �� �� �ֵ�
		//2)Head->next�б�
		//3)head = head->next
		//4)data���� ��ȯ
		//5) ���� ��� ����
	
		shared_ptr<Node> oldHead = std::atomic_load(&_head);

		while (oldHead && std::atomic_compare_exchange_weak(&_head, &oldHead, oldHead->next) == false)
		{
		}

		if (oldHead == nullptr)
			return shared_ptr<T>();

		return oldHead->data;
	}

private:
	shared_ptr<Node> _head;

};*/

template<typename T>
class LockFreeStack
{
	struct Node;
	struct CountedNodePtr
	{
		int32 externalCount = 0;
		Node* ptr = nullptr;
	};

	struct Node
	{
		Node(const T& value) : data(make_shared<T>(value))
		{}
		shared_ptr<T> data;
		atomic<int32> internalCount = 0;
		CountedNodePtr next;
	};

public:
	void Push(const T& value)
	{
		//1) ��� ����
		//2) �� ����� next�� ����
		//3) ��带 �� ����
		CountedNodePtr node;
		node.ptr = new Node(value);
		node.externalCount = 1;

		node.ptr->next = _head;
		while (_head.compare_exchange_weak(node.ptr->next, node))
		{
		}

	}

	shared_ptr<T> TryPop()
	{
		//1)Head �б� -> �б���� ���� �� �� �ֵ�
		//2)Head->next�б�
		//3)head = head->next
		//4)data���� ��ȯ
		//5) ���� ��� ����

		CountedNodePtr oldHead = _head;
		while (true)
		{
			//�������� ȹ��(externalCount�� +1�� �ְ� �̱�)
			IncreaseHeadCount(oldHead);
			// �ּ� externalCount>=2���״� ����x(�����ϰ� ���ٰ���)
			Node* ptr = oldHead.ptr;

			if (ptr == nullptr)
				return shared_ptr<T>();

			// �������� ȹ��(ptr->next�� head�� �ٲ�ġ���� �ְ� �̱�)
			if (_head.compare_exchange_strong(oldHead, ptr->next))
			{
				shared_ptr<T> res;
				res->swap(ptr->data);

				//external : 1 ���� -> ������ ȹ�濡�� 2(+1) -> �ٸ��ְ� ������ ȹ�� 4(�� +1 ��+2)
				//internal : 0 ����

				// ������ �� ���� �ִ°�
				const int32 countIncrease = oldHead.externalCount - 2;
				if (ptr->internalCount.fetch_add(countIncrease) == -countIncrease)
					delete ptr;


				return res;
			}
			else if(ptr->internalCount.fetch_sub(1) == 1)
			{
				//�������� ������� �������� ���� ->�޼��� ����
				delete ptr;
			}
		}
		

		return oldHead->data;
	}

private:
	void IncreaseHeadCount(CountedNodePtr& oldCounter)
	{
		while (true)
		{
			CountedNodePtr newCounter = oldCounter;
			newCounter.externalCount++;

			if (_head.compare_exchange_strong(oldCounter, newCounter))
			{
				oldCounter.externalCount = newCounter.externalCount;
				break;
			}

		}
	}
private:
	atomic<CountedNodePtr> _head;

};