#pragma once

class Board;
class Player
{

public:
	void		Init(Board* board);
	void		Update(uint64 deltaTime);
	void		SetPos(Pos pos) { _pos = pos; }
	const Pos&	GetPos() { return _pos; }

	

private:
	Pos			_pos = {};
	int32		_dir = DIR_UP;
	Board*		_board = nullptr;

	Pos			_dest = {};
};

