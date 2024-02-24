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

};