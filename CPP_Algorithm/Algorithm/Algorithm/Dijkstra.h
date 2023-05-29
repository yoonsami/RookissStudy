#pragma once
#include <vector>
#include <list>
using namespace std;
struct Vertex
{

};

class Dijkstra
{

public:
	void CreateGraph();
	void GraphDijkstra(int here);
public:
	vector<Vertex> _vertices;
	vector<vector<int>> _adjacent;

};

