#pragma once

class Board;
class Player
{
	enum
	{
		MOVE_TICK = 100
	};
public:
	void		Init(Board* board);
	void		Update(uint64 deltaTime);
	void		SetPos(const Pos& pos) { _pos = pos; }
	const Pos&	GetPos() { return _pos; }

private:
	void RightHand();
	void BFS();


	bool CanGo(const Pos& pos);
private:
	Pos			_pos = {};
	int32		_dir = DIR_UP;
	Board*		_board = nullptr;

	vector<Pos>	_path;
	uint32		_pathIndex = 0;
	uint64		_sumTick = 0;
};

