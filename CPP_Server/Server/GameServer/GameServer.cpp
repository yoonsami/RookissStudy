#include "pch.h"
#include "ThreadManager.h"
#include "Memory.h"


class Knight
{
public:
	Knight() : _hp(0) { cout << "Knight()" << endl; }
	Knight(int32 hp) : _hp(hp) { cout << "Knight(int)" << endl; }
	~Knight() { cout << "~Knight()" << endl; }


private:
	int32 _hp =0;
};

int main()
{

	for (int32 i = 0; i < 5; ++i)
	{
		GThreadManager->Launch([]()
			{
				while (true)
				{
					Vector<Knight> v(10);
					Map<int32, Knight> m;
					m[100] = Knight();

					this_thread::sleep_for(10ms);
				}
			});
	}

	//메모리 풀링
	// 메모리 파편화 방지
	// 할당 해제 반복횟수 줄임

	GThreadManager->Join();
}
