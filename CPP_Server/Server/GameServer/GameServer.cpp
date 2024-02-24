#include "pch.h"
#include "ThreadManager.h"

void ThreadManagerTest()
{
	while (true)
	{
		cout << "I am Thread " << LThreadId << endl;
		this_thread::sleep_for(1s);
	}
}

int main()
{
	for (int32 i = 0; i < 5; ++i)
	{
		GThreadManager->Launch(ThreadManagerTest);
	}

	GThreadManager->Join();
}
