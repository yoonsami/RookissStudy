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
		Node(const T& value) : data(value),next(nullptr), _pendingList(nullptr)
		{}
		T data;
		Node* next;
	};

public:
	void Push(const T& value)
	{
		//1) 노드 생성
		//2) 새 노드의 next를 헤드로
		//3) 헤드를 새 노드로
		Node* node = new Node(value);
		node->next = _head;
		
		while (_head.compare_exchange_weak(node->next, node) == false)
		{

		}

	}

	bool TryPop(T& value)
	{


		//1)Head 읽기 -> 읽기부터 문제 될 수 있따
		//2)Head->next읽기
		//3)head = head->next
		//4)data추출 반환
		//5) 추출 노드 삭제

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
		// GARBAGE Collector 잇으면 끝
		//없으면 누수 잡아야함
		// 잠시 삭제 보류
		TryDelete(oldHead);

		return true;
	}

	void TryDelete(Node* oldHead)
	{
		// 나 외에 누가 있는가
		if (_popCount == 1)
		{
			//혼자니까, 예약된 다른 데이터도 삭제해보자
			Node* node = _pendingList.exchange(nullptr);

			if (--_popCount == 0)
			{
				//아직도 혼자라면 -> 삭제 가능
				//여기서 누가 끼어들어도 이미 데이터 분리해서 상관ㄴ
				DeleteNodes(node);
			}
			else if(node)
			{
				//누가 끼어들었으니 다음에 하자.
				ChainPendingNodeList(node);

			}

			delete oldHead;
		}
		else
		{
			// 누가 있으니까, 삭제 예약만
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

	atomic<uint32> _popCount = 0; // Pop 실행중인 쓰레드 개수
	atomic<Node*> _pendingList; //삭제 되어야 할 노드들

};