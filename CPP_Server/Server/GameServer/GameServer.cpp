#include "pch.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <windows.h>
#include <future>

atomic<bool> ready;
int32 value;

void Producer()
{
	value = 10;
	ready.store(true, memory_order::memory_order_release);
}

void Consumer()
{
	while (ready.load(memory_order::memory_order_acquire) == false)
		;

	cout << value << endl;
}

int main()
{
	ready = false;
	value = 0;
	thread t1(Producer);
	thread t2(Consumer);
	t1.join();
	t2.join();
	//Memory Model 정책
	//1)Sequentially Consistent(seq_cst)
	//2)Acquire-Release(consume,acquire,release,acq_rel)
	//3)Relaxed(relaxed)

	// 1) seq_cst(컴파일러 최적화 여지 적음 = 직관적 = 가장 엄격)
	// 가시성문제 해결 코드 재배치 문제 해결


	// 2) acquire-release 
	// // release 명령 이전의 메모리 명령들이 해당 명령 이후로 재배치 되는걸 막음
	//acquire로 같은 변수를 읽는 쓰레드가 있다면 release 이전의 명령들이 acquire 하는 순간부터 관찰 가능(가시성)
	// 
	// 3) relaxed (자유롭다 = 컴파일러 최적화 여지 많음 = 직관적이지 않음)
	// 코드 재배치 멋대로, 가시성 해결 x
	// 동일 객체에 대한 동일 관전 순서만 보장
	
}
