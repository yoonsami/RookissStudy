#include "pch.h"
#include "ConsoleHelper.h"
#include "Board.h"
#include "Player.h"
Board board;
Player player;
int main()
{
	srand(static_cast<uint32>(time(nullptr)));

	board.Init(25,&player);
	player.Init(&board);
	uint64 lastTick = 0;


	while (true)
	{
#pragma region 프레임관리
		const uint64 currentTick = GetTickCount64();
		const uint64 deltaTick = currentTick - lastTick;
		lastTick = currentTick;
#pragma endregion

		player.Update(deltaTick);


		board.Render();



	}
}

