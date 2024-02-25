#include "pch.h"
#include "Memory.h"
#include "MemoryPool.h"

MemoryManager::MemoryManager()
{
	int32 size = 0;
	int32 tableIndex = 0;

	for (size = 32; size <= 1024; size += 32)
	{
		MemoryPool* pool = new MemoryPool(size);
		_pools.push_back(pool);

		while (tableIndex <= size)
		{
			_poolTable[tableIndex] = pool;
			tableIndex++;
		}
	}
	for (;size <= 2048; size += 128)
	{
		MemoryPool* pool = new MemoryPool(size);
		_pools.push_back(pool);

		while (tableIndex <= size)
		{
			_poolTable[tableIndex] = pool;
			tableIndex++;
		}
	}
	for (; size <= 4096; size += 256)
	{
		MemoryPool* pool = new MemoryPool(size);
		_pools.push_back(pool);

		while (tableIndex <= size)
		{
			_poolTable[tableIndex] = pool;
			tableIndex++;
		}
	}
}

MemoryManager::~MemoryManager()
{
	for (MemoryPool* pool : _pools)
		delete pool;

	_pools.clear();

}

void* MemoryManager::Allocate(int32 size)
{
	MemoryHeader* header = nullptr;
	const int32 allocSize = size + sizeof(MemoryHeader);

	if (allocSize > MAX_ALLOC_SIZE)
	{
		// �޸� ū �༮�� Ǯ�� ���ϰ� �׳� �Ҵ���
		header = reinterpret_cast<MemoryHeader*>(::malloc(allocSize));

	}
	else
	{
		// �޸�Ǯ���� �����´�
		header = _poolTable[allocSize]->Pop();
	}

	return MemoryHeader::AttachHeader(header,allocSize);
}

void MemoryManager::Release(void* ptr)
{
	MemoryHeader* header = MemoryHeader::DetachHeader(ptr);

	const int32 allocSize = header->allocSize;
	ASSERT_CRASH(allocSize > 0);

	if (allocSize > MAX_ALLOC_SIZE)
	{
		// �޸� Ǯ�� �Ƚ���
		::free(header);
	}
	else
	{
		//�޸�Ǯ�� �ݳ�
		_poolTable[allocSize]->Push(header);
	}
}
