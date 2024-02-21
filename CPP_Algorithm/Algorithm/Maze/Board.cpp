#include "pch.h"
#include "Board.h"
#include "Player.h"
#include "DisjointSet.h"
const char* TILE = "��";
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

//binary tree  �̷� ���� �˰���
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

	// edges �ĺ��� ���� cost�� ���
	for (int32 y = 0; y < _size; ++y)
	{
		for (int32 x = 0; x < _size; ++x)
		{
			if(_tile[y][x] == TileType::WALL) continue;

			// ���� �����ϴ� ���� �ĺ�
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

	//edges[u] : u�� ����� ���� ���
	map<Pos, vector<CostEdge>> edges;

	for (int32 y = 0; y < _size; ++y)
	{
		for (int32 x = 0; x < _size; ++x)
		{
			if (_tile[y][x] == TileType::WALL) continue;

			// ���� �����ϴ� ���� �ĺ�
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

	//�ش� ������ Ʈ���� ���ԵǾ��ֳ�
	map<Pos, bool> added;
	// ������ ���� ����
	map<Pos, Pos> parent;
	//������ ���� �� �ش� ������ ��� �ּ� ���� ����
	map<Pos, int32> best;

	//dijikstra�� ����

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

		// ��� �߰��� ������ ������ ���� �˻�
		for (auto& edge : edges[v])
		{
			// �̹� �ش� ���� �߰��Ǿ����� �н�
			if (added[edge.vtx]) continue;
			// �ٸ� ��η� �� ���� �ĺ� �߰��̸� �н�
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
