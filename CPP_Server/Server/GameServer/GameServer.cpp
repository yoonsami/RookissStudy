#include "pch.h"
#include "ThreadManager.h"
#include "Memory.h"
using TL = TypeList<class Player, class Mage, class Knight, class Archer>;
class Player
{
	
public:
	Player()
	{
		INIT_TL(Player);
	}


	virtual ~Player() {}

public:
	DECLARE_TL;
};

class Knight : public Player
{
public:
	Knight() { INIT_TL(Knight); }
};

class Mage : public Player
{
public:
	Mage() { INIT_TL(Mage); }
};

class Archer : public Player
{
public:
	Archer() { INIT_TL(Archer); }
};

class Dog 
{

};

int main()
{
	/*using TL = TypeList<Mage, Knight, Archer>;
	TL::Tail::Head who1;
	TL::Tail::Tail who2;
	TL::Head who3;

	int32 len1 = Length<TL>::value;

	TypeAt<TL, 0>::Result who4;

	int32 index1 = IndexOf<TL, Mage>::value;

	Conversion<Knight, Player>::exists;
	Conversion<Player, Knight>::exists;

	TypeConversion<TL> test;*/

	{
		Player* player = new Knight;

		bool canCast = CanCast<Knight*>(player);
		Knight* knight = TypeCast<Knight*>(player);

		delete player;

	}

	{
		shared_ptr<Knight> knight = MakeShared<Knight>();

		shared_ptr<Player> player =  TypeCast<Player>(knight);
		bool canCast = CanCast<Player>(knight);
	}

	for (int32 i = 0; i < 3; ++i)
	{
		GThreadManager->Launch([]()
			{
				while (true)
				{
					
				}


			});
	}

	GThreadManager->Join();
}
