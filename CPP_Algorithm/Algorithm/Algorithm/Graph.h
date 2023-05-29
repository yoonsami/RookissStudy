#pragma once
#include <vector>
using namespace std;
void CreateGraph1()
{
	struct Vertex
	{
		vector<Vertex*> edges;

	};

	vector<Vertex> v;
	v.resize(6);

	v[0].edges.push_back(&v[1]);
	v[0].edges.push_back(&v[3]);

	v[1].edges.push_back(&v[0]);
	v[1].edges.push_back(&v[2]);
	v[1].edges.push_back(&v[3]);

	v[3].edges.push_back(&v[4]);
	v[5].edges.push_back(&v[4]);

	// 0에서 3이 이어져있는가
	bool isConnected = false;
	for (Vertex* edge : v[0].edges)
	{
		if (edge == &v[3])
		{
			isConnected = true;
			break;
		}
	}
	// 실제 데이터와 간선 여부를 분리시키면 더 좋을 것 같음
}

void CreateGraph2()
{
	struct Vertex
	{

	};

	vector<Vertex> v;
	v.resize(6);

	vector<vector<int>> adjacent(6);

	adjacent[0] = { 1,3 };
	adjacent[1] = { 0,2,3 };
	adjacent[3] = { 4 };
	adjacent[5] = { 4 };

	// 0에서 3이 이어져있는가
	bool isConnected = false;
	for (int vertex : adjacent[0])
	{
		if (vertex == 3)
		{
			isConnected = true;
			break;
		}
	}

	bool isConnected2 = find(adjacent[0].begin(), adjacent[0].end(), 3) != adjacent[0].end();
	// 드문드문 연결되어있으면 괜찮지만, 빼곡하게 연결되어있으면 별로
}

void CreateGraph3()
{
	struct Vertex
	{

	};

	vector<Vertex> v;
	v.resize(6);

	vector<vector<bool>> adjacent(6, vector<bool>(6, false));

	adjacent[0][1] = true;
	adjacent[0][3] = true;

	adjacent[1][0] = true;
	adjacent[1][2] = true;
	adjacent[1][3] = true;

	adjacent[3][4] = true;
	adjacent[5][4] = true;

	bool isConnected = adjacent[0][3];

	// 가중치

	vector<vector<int>> adjacent2 =
	{
		vector<int> {-1,15,-1,35,-1,-1},
		vector<int> {15,-1,5,10,-1,-1},
		vector<int> {-1,-1,-1,-1,-1,-1},
		vector<int> {-1,-1,-1,-1,5,-1},
		vector<int> {-1,-1,-1,-1,-1,-1},
		vector<int> {-1,-1,-1,-1,5,-1}

	};


}