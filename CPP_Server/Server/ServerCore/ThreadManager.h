#pragma once

#include <thread>
#include <functional>

/*-----------------------
		ThreadManager
------------------------*/


class ThreadManager
{
	friend class CoreGlobal;
private:
	ThreadManager();
	~ThreadManager();

public:
	void	Launch(function<void(void)> callback);
	void	Join();


	static void InitTLS();
	static void DestoryTLS();

private:
	Mutex			_lock;
	vector<thread>	_threads;
};

