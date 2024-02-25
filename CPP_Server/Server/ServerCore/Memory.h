#pragma once
#include "Allocator.h"

class MemoryPool;

class MemoryManager
{
	enum
	{
		// ~1024까지 32단위, ~2048 128단위, ~4096 256단위
		POOL_COUNT = (1024 / 32) + (1024 / 128) + (2048 / 256),
		MAX_ALLOC_SIZE = 4096
	};
public:
	MemoryManager();
	~MemoryManager();

	void* Allocate(int32 size);
	void Release(void* ptr);

private:
	vector<MemoryPool*> _pools;

	// 메모리 크기 <-> 메모리 풀
	MemoryPool* _poolTable[MAX_ALLOC_SIZE + 1];
};

template<typename Type,typename... Args>
Type* xnew(Args&&... args)
{
	Type* memory = static_cast<Type*>(Xalloc(sizeof(Type)));

	// placement new 할당된 메모리 위에 생성자 호출
	new(memory)Type(forward<Args>(args)...);
	return memory;
}

template<typename Type>
void xdelete(Type* obj)
{
	// 소멸자 호출
	obj->~Type();

	Xrelease(obj);
}
