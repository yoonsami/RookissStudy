#include "pch.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <windows.h>

mutex m;
queue<int32> q;
HANDLE handle;

// User-Level Object(커널 오브젝트 X)
condition_variable cv;

//#include <condition_variable>
//condition_variable_any cv;

void Producer()
{
	while (true)
	{
		//Lock과 짝을 지어서 사용
		// 1) Lock을 잡고
		// 2) 공유 변수 값 수정
		// 3) Lock 해제
		// 4) 조건변수를 통해 다른 쓰레드에 통지

		{
			unique_lock<mutex> lock(m);
			q.push(100);
		}

		cv.notify_one(); // wait중인 쓰레드가 있으면 하나만 깨운다
	}
}

void Consumer()
{
	while (true)
	{

		unique_lock<mutex> lock(m);
		// 중간에 lock풀어주는 기능이 있어야해서 Lock_Guard 사용 불가
		cv.wait(lock, []() {return q.empty() == false; });
		// 1) Lock을 잡고
		// 2) 조건 확인
		// 3) 만족하면 빠져나와 코드 진행
		// 4) 만족하지 않는다면, Lock을 풀고 대기로 전환

		
		{
			int32 data = q.front();
			q.pop();
			cout << q.size() << endl;
		}
	}
}

int main()
{
	// 이벤트는 커널 오브젝트
	// Usage Count
	// Signal(파란불) / Non-Signal(빨간불) << bool
	// Auto / Manual Reset << bool
	//handle = ::CreateEvent(NULL/*보안속성*/, TRUE, FALSE, NULL);

	thread t1(Producer);
	thread t2(Consumer);

	t1.join();
	t2.join();

	//::CloseHandle(handle);
}
