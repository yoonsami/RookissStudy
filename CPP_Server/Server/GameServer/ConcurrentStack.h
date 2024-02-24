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
template<typename T>
class LockFreeStack
{
	struct Node
	{
		Node(const T& value) : data(value),next(nullptr), _pendingList(nullptr)
		{}
		T data;
		Node* next;
	};

public:
	void Push(const T& value)
	{
		//1) ��� ����
		//2) �� ����� next�� ����
		//3) ��带 �� ����
		Node* node = new Node(value);
		node->next = _head;
		
		while (_head.compare_exchange_weak(node->next, node) == false)
		{

		}

	}

	bool TryPop(T& value)
	{


		//1)Head �б� -> �б���� ���� �� �� �ֵ�
		//2)Head->next�б�
		//3)head = head->next
		//4)data���� ��ȯ
		//5) ���� ��� ����

		++_popCount;

		Node* oldHead = _head;
		while (oldHead && _head.compare_exchange_weak(oldHead, oldHead->next) == false)
		{

		}

		if (oldHead == nullptr)
		{
			--_popCount;
			return false;
		}

		//Exception X
		value = oldHead->data;
		// GARBAGE Collector ������ ��
		//������ ���� ��ƾ���
		// ��� ���� ����
		TryDelete(oldHead);

		return true;
	}

	void TryDelete(Node* oldHead)
	{
		// �� �ܿ� ���� �ִ°�
		if (_popCount == 1)
		{
			//ȥ�ڴϱ�, ����� �ٸ� �����͵� �����غ���
			Node* node = _pendingList.exchange(nullptr);

			if (--_popCount == 0)
			{
				//������ ȥ�ڶ�� -> ���� ����
				//���⼭ ���� ����� �̹� ������ �и��ؼ� �����
				DeleteNodes(node);
			}
			else if(node)
			{
				//���� ���������� ������ ����.
				ChainPendingNodeList(node);

			}

			delete oldHead;
		}
		else
		{
			// ���� �����ϱ�, ���� ���ุ
			ChainPendingNode(oldHead);
			--_popCount;
		}
	}

	void ChainPendingNodeList(Node* first, Node* last)
	{
		last->next = _pendingList;

		//Compare and Swap
		while (_pendingList.compare_exchange_weak(last->next,first) == false)
		{

		}
	}

	void ChainPendingNodeList(Node* node)
	{
		Node* last = node;
		while (last->next)
			last = last->next;

		ChainPendingNodeList(node, last);
	}

	void ChainPendingNode(Node* node)
	{
		ChainPendingNodeList(node, node);
	}

	static void DeleteNodes(Node* node)
	{
		while (node)
		{
			Node* next = node->next;
			delete node;
			node = next;
		}
	}

private:
	atomic<Node*> _head;

	atomic<uint32> _popCount = 0; // Pop �������� ������ ����
	atomic<Node*> _pendingList; //���� �Ǿ�� �� ����

};