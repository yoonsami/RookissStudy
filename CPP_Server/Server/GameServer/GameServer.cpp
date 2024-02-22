#include "pch.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <windows.h>
#include <future>

//쓰레드마다 고유하게 가질 정보가 된다
thread_local int32 LThreadId = 0;
thread_local queue<int32> q;

void ThreadMain(int32 threadId)
{
	LThreadId = threadId;

	while (true)
	{
		cout << "I am Thread " << LThreadId << endl;
		this_thread::sleep_for(1s);
	}
}

int main()
{
	vector<thread> threads;
	for (int32 i = 0; i < 10; ++i)
	{
		int32 threadId = i + 1;
		threads.push_back(thread(ThreadMain, threadId));
	}

	for (thread& t : threads)
		t.join();
	
}
