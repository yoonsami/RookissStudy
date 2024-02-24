#include "pch.h"
#include "ThreadManager.h"

// 소수 구하기 문제
atomic<int32> ans;

bool IsPrime(int32 num)
{
	if (num <= 1) return false;
	if (num == 2 || num == 3) true;

	for (int32 i = 2; i * i <= num; ++i)
		if (num % i == 0) return false;

	return true;
}

void Thread(int32 start, int32 end)
{
	for (int i = start; i < end; ++i)
	{
		if (IsPrime(i)) ans++;


	}



}


int main()
{
	ans = 0;
	const int MAX_NUMBER = 1000000;

	vector<thread> v;
	for (int32 i = 0; i < 1000; ++i)
	{
		v.push_back(thread(Thread, i * 1000, (i + 1) * 1000));

	}
	for (int32 i = 0; i < 1000; ++i)
	{
		v[i].join();
	}

	cout << ans << endl;
}
