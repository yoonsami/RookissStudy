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
		//1) 노드 생성
		//2) 새 노드의 next를 헤드로
		//3) 헤드를 새 노드로
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
		//1)Head 읽기 -> 읽기부터 문제 될 수 있따
		//2)Head->next읽기
		//3)head = head->next
		//4)data추출 반환
		//5) 추출 노드 삭제

		CountedNodePtr oldHead = _head;
		while (true)
		{
			//참조권한 획득(externalCount를 +1한 애가 이김)
			IncreaseHeadCount(oldHead);
			// 최소 externalCount>=2일테니 삭제x(안전하게 접근가능)
			Node* ptr = oldHead.ptr;

			if (ptr == nullptr)
				return shared_ptr<T>();

			// 소유권한 획득(ptr->next로 head를 바꿔치기한 애가 이김)
			if (_head.compare_exchange_strong(oldHead, ptr->next))
			{
				shared_ptr<T> res;
				res->swap(ptr->data);

				//external : 1 시작 -> 참조권 획득에서 2(+1) -> 다른애가 참조권 획득 4(나 +1 남+2)
				//internal : 0 시작

				// 나말고 또 누가 있는가
				const int32 countIncrease = oldHead.externalCount - 2;
				if (ptr->internalCount.fetch_add(countIncrease) == -countIncrease)
					delete ptr;


				return res;
			}
			else if(ptr->internalCount.fetch_sub(1) == 1)
			{
				//참조권은 얻었으나 소유권은 실패 ->뒷수습 내가
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