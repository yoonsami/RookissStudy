#include "pch.h"
#include "Player.h"
#include "Board.h"

void Player::Init(Board* board)
{
	_pos = board->GetEnterPos();
	_board = board;

	Pos pos = _pos;

	Pos dest = board->GetExitPos();
	
	while (pos != dest)
	{

		Pos front[4] = {
			{-1,0},
			{0,-1},
			{1,0},
			{0,1}
		};

		int32 newDir = (_dir - 1 + DIR_COUNT) % DIR_COUNT;


		if (_board->GetTileType(pos + front[newDir]) == TileType::EMPTY)
		{
			_dir = newDir;
			pos += front[newDir];
			_path.push_back(pos);
		}

		else if (_board->GetTileType(pos + front[_dir]) == TileType::EMPTY)
		{
			pos += front[_dir];
			_path.push_back(pos);
		}

		else
			_dir = (_dir + 1) % DIR_COUNT;

	}


	stack<Pos> s;
	for (int i = 0; i < _path.size() - 1; ++i)
	{
		if (!s.empty() && s.top() == _path[i + 1])
			s.pop();
		else
			s.push(_path[i]);
	}

	if (!_path.empty())
		s.push(_path.back());
	
	vector<Pos> path;
	while (!s.empty())
	{
		path.push_back(s.top());
		s.pop();
	}

	reverse(path.begin(), path.end());

	_path = path;
}

void Player::Update(uint64 deltaTime)
{
	if (_pathIndex >= _path.size())
		return;

	_sumTick += deltaTime;
	if (_sumTick >= MOVE_TICK)
	{
		_sumTick = 0;

		_pos = _path[_pathIndex];
		_pathIndex++;
	}
}
