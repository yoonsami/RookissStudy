#include "pch.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <windows.h>
#include <future>
atomic<bool> flag = false;
int main()
{
	flag = false;

	//if (flag.is_lock_free())
	//{
	//	//원래 원자적 처리 가능
	//}
	{
		flag = true;
		bool val = flag;
	}
	{
		flag.store(true);
		bool val = flag.load();
	}
	{
		flag.store(true,memory_order::memory_order_seq_cst);
		bool val = flag.load(memory_order::memory_order_seq_cst);
	}

	{
		bool prev = flag; // 다른 쓰레드에서 쓰고있으면 유효하지 않을 수 있음
		flag = true;

	}
	// ->
	{
		bool prev = flag.exchange(true);
	}

	//CAS 조건부 수정
	{
		bool expected = false;
		bool desired = true;
		flag.compare_exchange_strong(expected, desired);

		if (flag == expected)
		{
			flag = desired;
			return true;
		}
		else
		{
			expected = flag;
			return false;
		}
		// 사용법 똑같지만, Spurious Failure 문제가 있을 수 있음. while문 써서 사용할 것
		flag.compare_exchange_weak(expected, desired);
	}
}
