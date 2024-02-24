#include "pch.h"
#include "ThreadManager.h"

/*-----------------------
		ThreadManager
------------------------*/


ThreadManager::ThreadManager()
{
	//Main Thread
	InitTLS();
}

ThreadManager::~ThreadManager()
{
	Join();
}

void ThreadManager::Launch(function<void(void)> callback)
{
	LockGuard guard(_lock);

	_threads.push_back(thread([=]() {
		InitTLS();
		callback();
		DestoryTLS();
	}));
}

void ThreadManager::Join()
{
	for (thread& t : _threads)
	{
		if (t.joinable())
			t.join();
	}
	_threads.clear();
}

void ThreadManager::InitTLS()
{
	static Atomic<uint32> SThreadID = 1;
	LThreadId = SThreadID.fetch_add(1);
}

void ThreadManager::DestoryTLS()
{

}
