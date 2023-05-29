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

	// 0���� 3�� �̾����ִ°�
	bool isConnected = false;
	for (Vertex* edge : v[0].edges)
	{
		if (edge == &v[3])
		{
			isConnected = true;
			break;
		}
	}
	// ���� �����Ϳ� ���� ���θ� �и���Ű�� �� ���� �� ����
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

	// 0���� 3�� �̾����ִ°�
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
	// �幮�幮 ����Ǿ������� ��������, �����ϰ� ����Ǿ������� ����
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

	// ����ġ

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