
#include <iostream>
#include "MyTree.h"
#include <vector>
#include <queue>
#include <list>
using namespace std;

struct Vertex
{

};

vector<Vertex> vertex;
vector<vector<int>> adjacent;

void CreateGraph()
{
	vertex.resize(6);
	adjacent.resize(6, vector<int>(6, -1));
	adjacent[0][1] = 15;
	adjacent[0][3] = 35;
	adjacent[1][0] = 15;
	adjacent[1][2] = 5;
	adjacent[1][3] = 10;
	adjacent[3][4] = 5;
	adjacent[5][4] = 5;
}

void Dijikstra(int here)
{
	struct VertexCost
	{
		int vertex;
		int cost;
	};

	list<VertexCost> discovered;
	vector<int> best(6, INT32_MAX);
	vector<int > parent(6, -1);

	discovered.push_back({ here,0 });
	best[here] = 0;
	parent[here] = here;

	while (!discovered.empty())
	{
		
		list<VertexCost>::iterator bestIt;
		int bestCost = INT32_MAX;

		for (auto it = discovered.begin(); it != discovered.end(); ++it)
		{
			if (it->cost < bestCost)
			{
				bestCost = it->cost;
				bestIt = it;
			}
		}

		int cost = bestIt->cost;
		here = bestIt->vertex;
		discovered.erase(bestIt);

		if(cost > best[here]) continue;

		for (int there = 0; there < 6; ++there)
		{
			if(adjacent[here][there] == -1) continue;

			int nextCost = best[here] + adjacent[here][there];
			if(nextCost >= best[there]) continue;

			best[there] = nextCost;
			parent[there] = here;
			discovered.push_back({ there,nextCost });
		}


	}

}

int main()
{
	CreateGraph();


}