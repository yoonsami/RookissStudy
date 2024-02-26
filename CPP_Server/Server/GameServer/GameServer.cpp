#include "pch.h"
#include "ThreadManager.h"
#include "Memory.h"

class Knight
{
public:
	int32 _hp = rand() % 1000;
};

int main()
{
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
