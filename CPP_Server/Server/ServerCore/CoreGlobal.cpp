#include "pch.h"
#include "CoreGlobal.h"
#include "ThreadManager.h"
#include "DeadLockProfiler.h"
#include "Memory.h"
ThreadManager* GThreadManager = nullptr;
MemoryManager* GMemoryManager = nullptr;
DeadLockProfiler* GDeadLockProfiler = nullptr;
class CoreGlobal
{
public:
	CoreGlobal() 
	{
		GThreadManager = new ThreadManager();
		GMemoryManager = new MemoryManager;
		GDeadLockProfiler = new DeadLockProfiler();
	}
	~CoreGlobal()
	{
		delete GThreadManager;
		delete GMemoryManager;
		delete GDeadLockProfiler;
	}
} GCoreGlobal;
