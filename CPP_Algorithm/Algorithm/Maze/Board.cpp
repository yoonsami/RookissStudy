#include "pch.h"
#include "Board.h"
#include "Player.h"
#include "DisjointSet.h"
const char* TILE = "■";
Board::Board()
{
}

Board::~Board()
{
}

void Board::Init(int32 size, Player* player)
{
	_size = size;
	_player = player;
	GenerateMap_Prim();
}

void Board::Render()
{
	ConsoleHelper::SetCursorPos(0, 0);
	ConsoleHelper::ShowConsoleCursor(false);

	for (int32 y = 0; y < _size; ++y)
	{
		for (int32 x = 0; x < _size; ++x)
		{
			ConsoleColor color = GetTileColor(Pos{ y,x });
			ConsoleHelper::SetCursorColor(color);

			cout << TILE;
		}
		cout << endl;
	}
}

//binary tree  미로 생성 알고리즘
void Board::GenerateMap_Kruskal()
{
	struct CostEdge
	{
		int cost;
		Pos u;
		Pos v;

		bool operator<(CostEdge& other) const
		{
			return cost < other.cost;
		}
	};

	for (int32 y = 0; y < _size; ++y)
	{
		for (int32 x = 0; x < _size; ++x)
		{
			if (x % 2 == 0 || y% 2 == 0)
				_tile[y][x] = TileType::WALL;
			else
				_tile[y][x] = TileType::EMPTY;
		}
	}

	vector<CostEdge> edges;

	// edges 후보를 랜덤 cost로 등록
	for (int32 y = 0; y < _size; ++y)
	{
		for (int32 x = 0; x < _size; ++x)
		{
			if(_tile[y][x] == TileType::WALL) continue;

			// 우측 연결하는 간선 후보
			if (x < _size - 2)
			{
				const int32 randValue = rand() & 100;
				edges.push_back(CostEdge{ randValue,Pos{y,x},Pos{y,x + 2} });
			}

			if (y < _size - 2)
			{
				const int32 randValue = rand() % 100;
				edges.push_back(CostEdge{ randValue,Pos{y,x},Pos{y + 2,x} });
			}
		}
	}

	sort(edges.begin(), edges.end());

	DisjointSet sets(_size * _size);
	for (auto& edge : edges)
	{
		int u = edge.u.y * _size + edge.u.x;
		int v = edge.v.y * _size + edge.v.x;
		if(sets.Find(u) == sets.Find(v))
			continue;

		sets.Merge(u, v);

		int x = (edge.u.x + edge.v.x) / 2;
		int y = (edge.u.y + edge.v.y) / 2;

		_tile[y][x] = TileType::EMPTY;
	}

}

void Board::GenerateMap_Prim()
{
	struct CostEdge
	{
		int cost;
		Pos vtx;


		bool operator<(const CostEdge& other) const
		{
			return cost < other.cost;
		}
	};

	for (int32 y = 0; y < _size; ++y)
	{
		for (int32 x = 0; x < _size; ++x)
		{
			if (x % 2 == 0 || y % 2 == 0)
				_tile[y][x] = TileType::WALL;
			else
				_tile[y][x] = TileType::EMPTY;
		}
	}

	//edges[u] : u와 연결된 간선 목록
	map<Pos, vector<CostEdge>> edges;

	for (int32 y = 0; y < _size; ++y)
	{
		for (int32 x = 0; x < _size; ++x)
		{
			if (_tile[y][x] == TileType::WALL) continue;

			// 우측 연결하는 간선 후보
			if (x < _size - 2)
			{
				const int32 randValue = rand() & 100;
				Pos u = Pos{ y,x };
				Pos v = Pos{ y,x + 2 };
				edges[u].push_back(CostEdge{ randValue,v });
				edges[v].push_back(CostEdge{ randValue,u });
			}

			if (y < _size - 2)
			{
				const int32 randValue = rand() % 100;
				Pos u = Pos{ y,x };
				Pos v = Pos{ y + 2,x };
				edges[u].push_back(CostEdge{ randValue,v });
				edges[v].push_back(CostEdge{ randValue,u });
			}
		}
	}

	//해당 정점이 트리에 포함되어있나
	map<Pos, bool> added;
	// 누구에 의해 연결
	map<Pos, Pos> parent;
	//인접한 간선 중 해당 정점에 닿는 최소 간선 정보
	map<Pos, int32> best;

	//dijikstra랑 유사

	for (int32 y = 0; y < _size; ++y)
	{
		for (int32 x = 0; x < _size; ++x)
		{
			best[Pos{ y,x }] = INT32_MAX;
			
		}
	}

	priority_queue<CostEdge> pq;
	const Pos startPos = Pos{ 1,1 };
	pq.push(CostEdge{0,startPos});
	parent[startPos] = startPos;
	best[startPos] = 0;

	while (!pq.empty())
	{
		CostEdge bestEdge = pq.top();
		pq.pop();

		Pos v = bestEdge.vtx;

		if (added[v]) continue;

		added[v] = true;

		{
			int y = (parent[v].y + v.y) / 2;
			int x = (parent[v].x + v.x) / 2;
			_tile[y][x] = TileType::EMPTY;
		}

		// 방금 추가한 정점에 인접한 간선 검사
		for (auto& edge : edges[v])
		{
			// 이미 해당 정점 추가되었으면 패스
			if (added[edge.vtx]) continue;
			// 다른 경로로 더 좋은 후보 발견이면 패스
			if(edge.cost > best[edge.vtx]) continue;

			best[edge.vtx] = edge.cost;
			parent[edge.vtx] = v;
			pq.push( edge);
		}
	}

}

TileType Board::GetTileType(Pos pos)
{
	if (pos.x >= _size || pos.x < 0 || pos.y >= _size || pos.y < 0)
		return TileType::NONE;

	return _tile[pos.y][pos.x];
}

ConsoleColor Board::GetTileColor(Pos pos)
{
	if (GetExitPos() == pos)
		return ConsoleColor::BLUE;

	if (pos == _player->GetPos())
		return ConsoleColor::YELLOW;

	TileType tileType = GetTileType(pos);

	switch (tileType)
	{
	case TileType::EMPTY:
		return ConsoleColor::GREEN;
		break;
	case TileType::WALL:
		return ConsoleColor::RED;
		break;
	}

	return ConsoleColor::WHITE;
}
