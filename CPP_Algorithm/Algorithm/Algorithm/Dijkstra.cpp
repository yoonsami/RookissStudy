#include "Dijkstra.h"

void Dijkstra::CreateGraph()
{
	_vertices.resize(6);
	_adjacent = vector<vector<int>>(6, vector<int>(6, -1));
	_adjacent[0][1] = 15;
	_adjacent[0][3] = 35;
	_adjacent[1][0] = 15;
	_adjacent[1][2] = 5;
	_adjacent[1][3] = 10;
	_adjacent[3][4] = 5;
	_adjacent[5][4] = 5;
}

void Dijkstra::GraphDijkstra(int here)
{
	struct VertexCost
	{
		int vertex;
		int cost;
	};

	list<VertexCost> discovered;
	vector<int> best(6, INT32_MAX);
	vector<int> parent(6, -1);


	discovered.push_back({here,0});
	best[here] = 0;
	parent[here] = 0;

	while (!discovered.empty())
	{
		// 후보 찾음
		auto bestIter = discovered.begin();
		int bestCost = INT32_MAX;

		for (auto it = discovered.begin(); it != discovered.end(); ++it)
		{
			const int cost = it->cost;

			if (bestCost > cost)
			{
				bestCost = cost;
				bestIter = it;
			}
		}

		int cost = bestIter->cost;
		here = bestIter->vertex;
		discovered.erase(bestIter);

		if(best[here] < cost)
			continue;

		for (int there = 0; there < 6; ++there)
		{
			if(_adjacent[here][there] == -1)
				continue;

			int nextCost = best[here] + _adjacent[here][there];
			if(nextCost>= best[there])
				continue;

			discovered.push_back({ there,nextCost });
			best[there] = nextCost;
			parent[there] = here;


		}

	}

	int a = 0;
}
