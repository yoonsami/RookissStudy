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
	Pos pos = _pos;

	Pos dest = _board->GetExitPos();
	Pos front[4] = {
		{-1,0},
		{0,-1},
		{1,0},
		{0,1}
	};

	queue<Pos> q;
	map<Pos, bool> discovered;
	map<Pos, Pos> parent;

	q.push(pos);
	discovered[pos] = true;
	parent[pos] = pos;

	while (!q.empty())
	{
		pos = q.front();
		q.pop();

		if(pos == dest) break;

		for (int dir = 0; dir < 4; ++dir)
		{
			Pos nextPos = pos + front[dir];
			if (!CanGo(nextPos)) continue;
			if (discovered[nextPos]) continue;

			discovered[nextPos] = true;
			parent[nextPos] = pos;
			q.push(nextPos);
		}
	}

	_path.clear();
	pos = dest;
	while (true)
	{
		_path.push_back(pos);
		if(parent[pos]==pos) break;
		pos = parent[pos];
	}

	reverse(_path.begin(), _path.end());
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
	Pos start = _pos;
	enum {DIR_COUNT = 4};
	Pos dest = _board->GetExitPos();
	Pos front[] = {
		{-1,0},
		{0,-1},
		{1,0},
		{0,1},
		{-1,-1},
		{-1,1},
		{1,-1},
		{1,1}
	};
	int cost[] = { 10,10,10,10,14,14,14,14 };

	struct PQNode
	{
		int f;
		int g;
		Pos p;
		bool operator<(const PQNode& other) const
		{
			return f < other.f;
		}
		bool operator>(const PQNode& other) const
		{
			return !(*this < other);
		}
	};
	int size = _board->GetSize();
	priority_queue<PQNode> pq;
	map<Pos, bool> closed;
	map<Pos, Pos> parent;
	vector<vector<int>> best(size, vector<int>(size, INT32_MAX));
	{
		int g = 0;
		int h = 10 * (abs(start.y - dest.y) + abs(start.x - dest.x));
		pq.push({ g + h,g,start });
		parent[start] = start;
		best[start.y][start.x] = g + h;
	}
	
	while (!pq.empty())
	{
		PQNode node = pq.top();
		int bestCost = node.f;
		pq.pop();

		if (closed[node.p]) continue;
		// or
		if (best[node.p.y][node.p.x] < bestCost) continue;
		closed[node.p] = true;

		if (node.p == dest) break;

		for (int dir = 0; dir < DIR_COUNT; ++dir)
		{
			Pos nextPos = node.p + front[dir];

			if(!CanGo(nextPos)) continue;
			if (closed[nextPos]) continue;

			{
				int g = node.g + cost[dir];
				int h = 10 * (abs(dest.x - nextPos.x) + abs(dest.y - nextPos.y));

				if(best[nextPos.y][nextPos.x] <= g + h) continue;

				pq.push({ g + h,h,nextPos });

				parent[nextPos] = node.p;
				best[nextPos.y][nextPos.x] = g + h;
			}
		}
	}

	_path.clear();
	_pathIndex = 0;
	Pos pos = dest;
	while (true)
	{
		_path.push_back(pos);
		if (parent[pos] == pos) break;
		pos = parent[pos];
	}

	reverse(_path.begin(), _path.end());
}

bool Player::CanGo(const Pos& pos)
{
	return _board->GetTileType(pos) == TileType::EMPTY;
}
