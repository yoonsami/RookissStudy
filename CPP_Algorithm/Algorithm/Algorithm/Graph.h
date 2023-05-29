#pragma once
#include <vector>
#include <queue>
using namespace std;
struct Vertex
{
	// data;
	bool _visited = false;
	bool _discovered = false;
	int _parent = -1;
	int _distance = -1;
};

class Graph
{

public:
	void CreateGraph();
	void DFS(int here);
	void BFS(int here);
public:
	vector<Vertex> _vertices;
	vector<vector<int>> _adjacent;

};

