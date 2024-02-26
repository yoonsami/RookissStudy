#pragma once
#include "Allocator.h"

class MemoryPool;

class MemoryManager
{
	enum
	{
		// ~1024���� 32����, ~2048 128����, ~4096 256����
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

	// �޸� ũ�� <-> �޸� Ǯ
	MemoryPool* _poolTable[MAX_ALLOC_SIZE + 1];
};

template<typename Type,typename... Args>
Type* xnew(Args&&... args)
{
	Type* memory = static_cast<Type*>(PoolAllocator::Alloc(sizeof(Type)));

	// placement new �Ҵ�� �޸� ���� ������ ȣ��
	new(memory)Type(forward<Args>(args)...);
	return memory;
}

template<typename Type>
void xdelete(Type* obj)
{
	// �Ҹ��� ȣ��
	obj->~Type();

	PoolAllocator::Release(obj);
}

template <typename Type>
shared_ptr<Type> MakeShared()
{
	return shared_ptr<Type>{xnew<Type>(), xdelete<Type>};
}