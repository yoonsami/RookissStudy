#include "pch.h"
#include "MemoryPool.h"

MemoryPool::MemoryPool(int32 allocSize) : _allocSize(allocSize)
{
}

MemoryPool::~MemoryPool()
{
    while (!_queue.empty())
    {
        MemoryHeader* header = _queue.front();
        _queue.pop();
        ::free(header);
    }
}

void MemoryPool::Push(MemoryHeader* ptr)
{
    WRITE_LOCK;
    ptr->allocSize = 0;

    // Pool�� �޸� �ݳ�
    _queue.push(ptr);

    _allocCount.fetch_sub(1);
}

MemoryHeader* MemoryPool::Pop()
{
    MemoryHeader* header = nullptr;
    {
        WRITE_LOCK;
        //Pool�� ������ �ִ°�
        if (!_queue.empty())
        {
            //������ �����´�
            header = _queue.front();
            _queue.pop();
        }
    }

    //������ ���� �����
    if (header == nullptr)
    {
        header = reinterpret_cast<MemoryHeader*>(::malloc(_allocSize));
    }
    else
    {
        ASSERT_CRASH(header->allocSize == 0);
    }

    _allocCount.fetch_add(1);

    return header;
}
