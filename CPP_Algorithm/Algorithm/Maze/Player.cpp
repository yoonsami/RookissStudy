#include "pch.h"
#include "Player.h"
#include "Board.h"

void Player::Init(Board* board)
{
	_pos = board->GetEnterPos();
	_board = board;

	BFS();
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

	Pos pos = _pos;

	Pos dest = _board->GetExitPos();
	Pos front[4] = {
		{-1,0},
		{0,-1},
		{1,0},
		{0,1}
	};

	const int32 size = _board->GetSize();
	vector<vector<bool>> discovered(size,vector<bool>(size,false));

	//vector<vector<Pos>> parent;
	map<Pos, Pos> parent;

	queue<Pos> q;
	q.push(pos);
	discovered[pos.y][pos.x] = true;
	parent[pos] = pos;

	while (!q.empty())
	{
		pos = q.front();
		q.pop();

		if(pos == dest)
			break;

		for (int32 dir = 0; dir < 4; ++dir)
		{
			Pos nextPos = pos + front[dir];

			if(!CanGo(nextPos))
				continue;

			if(discovered[nextPos.y][nextPos.x])
				continue;

			q.push(nextPos);
			discovered[nextPos.y][nextPos.x] = true;
			parent[nextPos] = pos;
		}
	}

	_path.clear();

	pos = dest;

	while (true)
	{
		_path.push_back(pos);

		if(pos == parent[pos])
			break;

		pos = parent[pos];
	}

	reverse(_path.begin(), _path.end());



}

bool Player::CanGo(const Pos& pos)
{
	return _board->GetTileType(pos) == TileType::EMPTY;
}
