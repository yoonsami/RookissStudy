#include "pch.h"
#include "ThreadManager.h"
#include "Memory.h"

class Knight
{
public:
	int32 _hp = rand() % 1000;
};

class Monster
{
public:
	int64 _id = 0;
};

int main()
{
	Knight* k = ObjectPool<Knight>::Pop();

	ObjectPool<Knight>::Push(k);

	shared_ptr<Knight> sptr = make_shared<Knight>();//기본적인 new delete ->풀링 못함
	shared_ptr<Knight> spa = ObjectPool<Knight>::MakeShared(); // objectpool 사용
	shared_ptr<Knight> test = MakeShared<Knight>();

	for (int32 i = 0; i < 3; ++i)
	{
		GThreadManager->Launch([]()
			{
				while (true)
				{
					Knight* knight = xnew<Knight>();
					cout << knight->_hp << endl;

					this_thread::sleep_for(10ms);
					xdelete(knight);
				}


			});
	}

	GThreadManager->Join();
}
