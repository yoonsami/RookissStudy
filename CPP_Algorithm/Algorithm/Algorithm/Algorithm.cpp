﻿#include <string>
#include <vector>
#include <queue>
#include <iostream>
using namespace std;

void BubbleSort(vector<int>& v)
{
	const int n = (int)v.size();
	for (int i = 0; i < n - 1; ++i)
	{
		for (int j = 0; j < n - 1 - i; ++j)
		{
			if (v[j] > v[j + 1]) swap(v[j], v[j + 1]);
		}
	}
}

void SelectionSort(vector<int>& v)
{
	const int n = (int)v.size();
	for (int i = 0; i < n - 1; ++i)
	{
		int bestIdx = i;
		for (int j = i + 1; j < n; ++j)
		{
			if (v[j] < v[bestIdx])
				bestIdx = j;
		}


		swap(v[i], v[bestIdx]);

	}
}

void InsertionSort(vector<int>& v)
{

	const int n = (int)v.size();

	for (int i = 1; i < n; ++i)
	{
		int insertData = v[i];
		int j;
		for (j = i - 1; j >= 0; j--)
		{
			if (v[j] > insertData)
				v[j + 1] = v[j];
			else break;
		}

		v[j + 1] = insertData;
	}
}

// 힙 정렬
void HeapSort(vector<int>& v)
{
	priority_queue<int, vector<int>, greater<int>> pq;

	for (int num : v) pq.push(num);
	v.clear();

	while (!pq.empty())
	{
		v.push_back(pq.top());       
		pq.pop();
	}
}

void MergeResult(vector<int>& v, int left, int mid, int right)
{
	vector<int> tmp;
	int leftIdx = left;
	int rightIdx = mid + 1;

	while (leftIdx <= mid && rightIdx << right)
	{
		if (v[leftIdx] <= v[rightIdx])
		{
			tmp.push_back(v[leftIdx]);
			leftIdx++;
		}
		else
		{
			tmp.push_back(v[rightIdx]);
			rightIdx++;
		}
	}

	if (leftIdx >= mid)
	{
		while (rightIdx<=right)
		{
			tmp.push_back(v[rightIdx]);
			rightIdx++;
		}
	}
	else
	{
		while (leftIdx<=mid)
		{
			tmp.push_back(v[leftIdx]);
			leftIdx++;
		}
	}

	for (int i = 0; i < tmp.size(); ++i)
		v[left + i] = tmp[i];
}

// 병합 정렬
// 분할 정복
void MergeSort(vector<int>& v,int left, int right)
{
	if (left >= right)
		return;

	int mid = (left + right) / 2;
	MergeSort(v, left, mid);
	MergeSort(v, mid + 1, right);
	
	MergeResult(v, left, mid, right);


}

int Partition(vector<int>& v, int left, int right)
{
	int pivot = v[left];
	int low = left + 1;
	int high = right;

	while (low <= high)
	{
		while (low <= right&&pivot >= v[low]) low++;

		while (high >= left + 1 && pivot <= v[high]) high--;

		if (low < high)
			swap(v[low], v[high]);
	}

	swap(v[left], v[high]);

	return high;
}

void QuickSort(vector<int>& v, int left, int right)
{
	if (left > right)
		return;

	int pivot = Partition(v, left, right);
	QuickSort(v, left, pivot - 1);
	QuickSort(v, pivot+1, right);


}

// map vs hash_map(unordered_map)
// 
// map : red black tree
// - 추가 탐색 삭제 -> O(logN)
// 
// unordered_map
// - 추가 탐색 삭제 -> O(1) : 제약조건이 있긴 함
// 메모리를 내주고 속도를 취한다
//'해시' '테이블'
//
//

class DisjointSet
{
public:
	DisjointSet(int n) : _parent(n)
	{
		for (int i = 0; i < n; ++i)
			_parent[i] = i;
	}

	int Find(int u)
	{
		if (_parent[u] == u) return u;

		return _parent[u] = Find(_parent[u]);
	}

	void Merge(int u, int v)
	{
		u = Find(u);
		v = Find(v);

		if (u == v) return;

		if (_rank[u] > _rank[v]) swap(u, v);

		_parent[u] = v;

		if (_rank[u] == _rank[v]) _rank[v]++;
	}


private:
	vector<int> _parent;
	vector<int> _rank;
};

// 동적 계획법
// 
// 
// 부분수열
// LIS(Longest Increasing Sequence)
// 제일 긴 순 증가 부분 수열의 길이


// 틱택토
using BoardType = vector<vector<char>>;
BoardType board;
int cache[19683];

bool IsFinished(const BoardType& board, char turn)
{
	for (int i = 0; i < 3; ++i)
		if (board[i][0] == turn && board[i][1] == turn && board[i][2] == turn)
			return true;

	for (int i = 0; i < 3; ++i)
		if (board[0][i] == turn && board[1][i] == turn && board[2][i] == turn)
			return true;

	if (board[0][0] == turn && board[1][1] == turn && board[2][2] == turn)
		return true;

	if (board[0][2] == turn && board[1][1] == turn && board[2][0] == turn)
		return true;

	return false;
}

enum {
	DEFAULT = 2,
	WIN =1,
	DRAW = 0,
	LOSE = -1
};

int HashKey(const BoardType& board)
{
	int ret = 0;
	for (int y = 0; y < 3; ++y)
	{
		for (int x = 0; x < 3; ++x)
		{
			ret = ret * 3;

			if (board[y][x] == 'o')
				ret += 1;
			else if (board[y][x] == 'x')
				ret += 2;
		}
	}
	return ret;
}

int CanWin(BoardType& board, char turn)
{
	// 기저 사례
	if (IsFinished(board, 'o' + 'x' - turn))
		return LOSE;

	// 캐시 확인
	int key = HashKey(board);
	int& ret = cache[key];
	if (ret != DEFAULT)
		return ret;

	int minValue = DEFAULT;

	for (int y = 0; y < 3; ++y)
	{
		for (int x = 0; x < 3; ++x)
		{
			if(board[y][x] != '.')
				continue;

			board[y][x] = turn;

			minValue = min(minValue, CanWin(board, 'o' + 'x' - turn));

			board[y][x] = '.';


		}
	}

	if (minValue == DRAW || minValue == DEFAULT)
		return ret = DRAW;

	return ret = -minValue;
}



int N;

int cache2[9999];

int Enchant(int num)
{
	if (num > N)
		return 0;

	if (num == N)
		return 1;

	int& ret = cache2[num];
	if (ret != -1)
		return ret;

	return ret = Enchant(num+1) + Enchant(num+2) + Enchant(num+3);
}

#include <string>
#include <vector>

using namespace std;
int maxGap = -1;
vector<int> answer;
void dfs(int count, int n, vector<int>& rian, vector<int>& info)
{
	if (count == n)
	{
		for (int i = 0; i <= n; ++i)
		{
			cout << rian[i] << " ";
		}
		cout << endl;
		int rianTotal = 0;
		int apeachTotal = 0;
		for (int i = 0; i <= 10; ++i)
		{
			if (rian[i] > info[i]) rianTotal += 10 - i;
			else apeachTotal += 10 - i;
		}

		if (rianTotal <= apeachTotal) return;

		if (maxGap < rianTotal - apeachTotal)
		{
			maxGap = rianTotal - apeachTotal;
			answer = rian;
		}
		else if (maxGap == rianTotal - apeachTotal)
		{
			for (int i = 10; i >= 0; --i)
			{
				if (answer[i] < rian[i])
				{
					answer = rian;
					return;
				}
			}
		}
		return;
	}


	for (int i = 0; i <= 10; ++i)
	{
	
		rian[i]++;
		dfs(count + 1, n, rian, info);
		rian[i]--;

	}


}

#include <string>
#include <vector>
#include <queue>
#include <map>
#include <iostream>



using namespace std;

struct Pos
{

	int y = 0;
	int x = 0;
	int dir = 0;

	bool operator<(Pos& other) { if (y != other.y)return y < other.y; return x < other.x; }
	bool operator<(const Pos& other)  const { if (y != other.y)return y < other.y; return x < other.x; }
	Pos& operator+=(const Pos& other) { y += other.y; x += other.x; return(*this); }
	Pos operator+(const Pos& other) { return{ y + other.y,x + other.x }; }
	bool operator==(Pos& other) { return (other.x == x && other.y == y); }
	bool operator!=(Pos& other) { return !((*this) == other); }
};

Pos front[4] = { {1,0},{0,1},{-1,0},{0,-1} };

int solution(vector<vector<int>> board) {
	int answer = 0;
	int size = board.size();
	vector<vector<int>>cost(size,vector<int>(size,INT32_MAX));

	Pos startPos = { 0,0,-1 };
	Pos dest = { size - 1,size - 1 };
	Pos curPos = startPos;

	queue<Pos> q;
	q.push(startPos);

	cost[startPos.y][startPos.x] = 0;

	while (!q.empty())
	{
		curPos = q.front();
		q.pop();

		if (curPos == dest)
		{
			answer = min(answer, cost[dest.y][dest.x]);
			continue;
		}

		for (int dir = 0; dir < 4; ++dir)
		{
			Pos newPos = curPos + front[dir];

			if (newPos.x < 0 || newPos.x >= size || newPos.y < 0 || newPos.y >= size) continue;

			if(board[newPos.y][newPos.x] == 1) continue;

			int newCost = cost[curPos.y][curPos.x];
			if (curPos.dir == -1) newCost += 100;
			else if (curPos.dir == dir) newCost += 100;
			else newCost += 600;

			if(newCost > cost[newPos.y][newPos.x]) continue;

			cost[newPos.y][newPos.x] = newCost;
			newPos.dir = dir;
			q.push(newPos);

		}
	}

	return answer = cost[dest.y][dest.x];
}

struct Shoe
{
	Shoe(int a, int b, int c, int d)
	{
		time = a;
		start = a + b;
		end = a + b + c;
		speed = d;
	}
	int time;
	int start;
	int end;
	int speed;
};

int T;
vector<Shoe> shoes;
vector<int>cache4;

// now번 신발을 신고 갈 수 있는 최대 거리
int Solve(int now)
{
	// 기저 사례
	if (now >= shoes.size())
		return 0;


	// 캐시
	int& ret = cache[now];
	if (ret != -1)
		return ret;

	// 적용
	Shoe& shoe = shoes[now];

	int dist = (shoe.end - shoe.start) * shoe.speed + (T -shoe.end) * 1;
	ret = max(ret, dist);

	// 다른 신발
	for (int next = now + 1; next < shoes.size(); next++)
	{
		Shoe& nextShoe = shoes[next];
		if(nextShoe.time < shoe.start) continue;

		// 다음 신발까지 이동거리
		int moveDist = 0;
		// 신발 지속 중 등장한 경우
		if (nextShoe.time <= shoe.end)
		{
			moveDist = (nextShoe.time - shoe.start) * shoe.speed;
		}
		else
		{
			moveDist = (shoe.end - shoe.start) * shoe.speed + (nextShoe.time - shoe.end) * 1;
		}

		ret = max(ret, moveDist + Solve(next));
	}

	return ret;
}

int main()
{
	T = 20;
	shoes.push_back(Shoe(0, 0, T, 1));
	shoes.push_back(Shoe(3,4,10,3));
	shoes.push_back(Shoe(4,1,4,2));
	shoes.push_back(Shoe(10,2,5,5));
	shoes.push_back(Shoe(15,1,3,7));
	sort(shoes.begin(), shoes.end(), [=](Shoe& left, Shoe& right) {return left.time < right.time; });
	cache4 = vector<int>(shoes.size() ,- 1);


	return 0;
}