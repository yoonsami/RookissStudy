#include "pch.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <windows.h>
#include <future>

int64 Calculate()
{
	int64 sum = 0;

	for (int32 i = 0; i < 100000; ++i)
		sum += i;
	return sum;
}

void PromiseWorker(promise<string>&& promise)
{
	promise.set_value("SecretMessage");
}

void TaskWorker(packaged_task<int64(void)>&& task)
{
	task();
}

int main()
{
	//동기(synchronous)실행
	Calculate();

	//비동기 실행(멀티쓰레드와는 다름)

	// 단기알바 느낌
	{
		//1)deferred - > lazy evaluation( 그냥 나중에 실행 )
		//2)async - > 별도 쓰레드 생성해서 실행
		// 3) deferred | async -> 알아서
		std::future<int64> future = std::async(std::launch::async, Calculate);

		// TODO
		std::future_status status = future.wait_for(1ms);
		if (future_status::ready == status) {}

		int64 sum = future.get();
	}

	{
		// 미래에 결과물 반환해줄것이라 약속
		std::promise<string> promise;
		future<string> future = promise.get_future();

		thread t(PromiseWorker, std::move(promise));


		cout <<future.get() << endl;
		t.join();


	}

	{
		//
		std::packaged_task<int64(void)> task(Calculate);
		std::future<int64> future = task.get_future();

		thread t(TaskWorker, move(task));

		int64 sum = future.get();
		cout << sum << endl;

		t.join();

	}
}
