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

	//인접 행렬 + 가중치
	_adjacent.resize(6, vector<int>(6, -1));
	_adjacent[0][1] = 15;
	_adjacent[0][3] = 5;
	_adjacent[1][0] = 3;
	_adjacent[1][2] = 1;
	_adjacent[1][3] = 1;
	_adjacent[3][4] = 1;
	_adjacent[5][4] = 1;
}

void Graph::DFS(int here)
{
	_vertices[here]._visited = true;
	
	
}

void Graph::BFS(int here)
{
	
}
