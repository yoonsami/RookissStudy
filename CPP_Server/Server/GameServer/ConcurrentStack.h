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
	// Empty라고 판단해도 Pop하는 순간에 다른 쓰레드에서
	데이터를 추가할 수 있기 때문에 생각하는 empty의 역할을 몬함
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
		//1) 노드 생성
		//2) 새 노드의 next를 헤드로
		//3) 헤드를 새 노드로
		shared_ptr<Node> node = make_shared<Node>(value);
		node->next = std::atomic_load(&_head);

		while (std::atomic_compare_exchange_weak(&_head, &node->next, node) == false)
		{
		}
	}

	shared_ptr<T> TryPop()
	{
		//1)Head 읽기 -> 읽기부터 문제 될 수 있따
		//2)Head->next읽기
		//3)head = head->next
		//4)data추출 반환
		//5) 추출 노드 삭제
	
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