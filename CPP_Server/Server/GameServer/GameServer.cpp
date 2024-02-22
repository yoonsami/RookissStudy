#include "pch.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <windows.h>
#include <future>

#include "ConcurrentQueue.h"
#include "ConcurrentStack.h"

queue<int32> q;
stack<int32> s;

LockQueue<int32> lq;
LockStack<int32> ls;

void Push()
{
	while (true)
	{
		int32 value = rand() % 100;
		lq.Push(value);


	}
}
void Pop()
{
	while (true)
	{
		int32 data = 0;
		if(lq.TryPop(OUT data))
			cout << data << endl;
	}
}

int main()
{
	thread t1(Push);
	thread t2(Pop);

	t1.join();
	t2.join();
	
}
