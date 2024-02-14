#include "pch.h"
#include "Player.h"
#include "Board.h"
#include <queue>

void Player::Init(Board* board)
{
	_pos = board->GetEnterPos();
	_board = board;

	AStar();
}

void Player::Update(uint64 deltaTime)
{
	if (_pathIndex >= _path.size())
	{
		_board->GenerateMap();
		Init(_board);
		return;
	}

	_sumTick += deltaTime;
	if (_sumTick >= MOVE_TICK)
	{
		_sumTick = 0;

		_pos = _path[_pathIndex];
		_pathIndex++;
	}
}

void Player::RightHand()
{
	Pos pos = _pos;

	_path.clear();
	_path.push_back(pos);

	Pos dest = _board->GetExitPos();
	Pos front[4] = {
		{-1,0},
		{0,-1},
		{1,0},
		{0,1}
	};

	while (pos != dest)
	{


		int32 newDir = (_dir - 1 + DIR_COUNT) % DIR_COUNT;


		if (CanGo(pos + front[newDir]))
		{
			_dir = newDir;
			pos += front[newDir];
			_path.push_back(pos);
		}

		else if (CanGo(pos + front[_dir]))
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

void Player::BFS()
{
	
}

struct PQNode
{
	bool operator<(const PQNode& node) const{return f < node.f;}
	bool operator>(const PQNode& node) const{return f > node.f;}
	int32 f;
	int32 g;
	Pos pos;
};

void Player::AStar()
{
	

}

bool Player::CanGo(const Pos& pos)
{
	return _board->GetTileType(pos) == TileType::EMPTY;
}
