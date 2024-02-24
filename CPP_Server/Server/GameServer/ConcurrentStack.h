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
		Node(const T& value) : data(value),next(nullptr)
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

		Node* oldHead = _head;
		while (oldHead && _head.compare_exchange_weak(oldHead, oldHead->next) == false)
		{

		}

		if (oldHead == nullptr) return false;
		//Exception X
		value = oldHead->data;
		// GARBAGE Collector ������ ��
		//������ ���� ��ƾ���
		// ��� ���� ����


		return true;
	}

private:


	atomic<Node*> _head;
	


};