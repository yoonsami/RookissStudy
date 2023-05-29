#include "Graph.h"

void Graph::CreateGraph()
{
	_vertices.resize(6);

	//인접 리스트
	/*_adjacent = vector<vector<int>>(6);
	_adjacent[0].push_back(1);
	_adjacent[0].push_back(3);
	_adjacent[1].push_back(0);
	_adjacent[1].push_back(2);
	_adjacent[1].push_back(3);
	_adjacent[3].push_back(4);
	_adjacent[5].push_back(4);*/

	//인접 행렬
	_adjacent.resize(6, vector<int>(6, 0));
	_adjacent[0][1] = 1;
	_adjacent[0][3] = 1;
	_adjacent[1][0] = 1;
	_adjacent[1][2] = 1;
	_adjacent[1][3] = 1;
	_adjacent[3][4] = 1;
	_adjacent[5][4] = 1;
}

void Graph::DFS(int here)
{
	_vertices[here]._visited = true;
	
	// 인접 리스트
	/*for (size_t i = 0; _adjacent[here].size(); ++i)
	{
		int there = _adjacent[here][i];
		if (!_vertices[there]._visited)
			DFS(there);
	}*/

	//인접 행렬
	for (int there = 0; there < 6; ++there)
	{
		if(_adjacent[here][there] == 0)
			continue;

		if(_vertices[there]._visited)
			continue;

		DFS(there);
	}
}

void Graph::BFS(int here)
{
	queue<int> q;
	q.push(here);

	_vertices[here]._discovered = true;

	_vertices[here]._parent = here;
	_vertices[here]._distance = 0;
	// 인접 리스트
	/*while (!q.empty())
	{
		here = q.front();
		q.pop();

		for (int there : _adjacent[here])
		{
			if(_vertices[there]._discovered)
				continue;

			q.push(there);
			_vertices[there]._discovered = true;

			_vertices[there]._parent = here;
			_vertices[there]._distance = _vertices[here]._distance + 1;
		}
	}*/
	
	//인접 행렬
	while (!q.empty())
	{
		here = q.front();
		q.pop();

		for (int there = 0; there < 6; ++there)
		{
			if(_adjacent[here][there] == 0)
				continue;

			if(_vertices[there]._discovered)
				continue;

			q.push(there);
			_vertices[there]._discovered = true;

			_vertices[there]._parent = here;
			_vertices[there]._distance = _vertices[here]._distance + 1;
		}
	}

	int a = 0;
}
