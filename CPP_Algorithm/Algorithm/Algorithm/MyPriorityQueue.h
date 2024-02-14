#pragma once
#include <vector>
using namespace std;
template <typename T, typename Container = vector<T>>
class PriorityQueue
{

public:
	void push(const T& value)
	{
		// 구조 결정
		{
			_data.push_back(value);

			int nowIndex = static_cast<int>(_data.size() - 1);

			while (nowIndex > 0)
			{
				int parentIndex = (nowIndex - 1) / 2;
				if (_data[parentIndex] > _data[nowIndex])
					break;

				::swap(_data[nowIndex], _data[parentIndex]);

				nowIndex = parentIndex;
			}
		}

		_data.push_back(value);

		int now = static_cast<int>(_data.size());

		while (now > 0)
		{
			int parent = (now - 1) / 2;
			if(_data[parent] > _data[now])
				break;

			swap(_data[parent], _data[now]);
			now = parent;


		}
	}
	T& top()
	{
		return _data[0];
	}
	void pop()
	{
		{
			_data[0] = _data.back();
			_data.pop_back();

			int nowIndex = 0;
			while (true)
			{
				int leftChildIndex = 2 * nowIndex + 1;
				int rightChildIndex = 2 * nowIndex + 2;

				if (leftChildIndex >= _data.size())
					break;

				int nextIndex = nowIndex;

				if (_data[leftChildIndex] > _data[nextIndex])
					nextIndex = leftChildIndex;

				if (rightChildIndex < _data.size() && _data[nextIndex] < _data[rightChildIndex])
					nextIndex = rightChildIndex;

				if (nextIndex == nowIndex)
					break;

				::swap(_data[nowIndex], _data[nextIndex]);
				nowIndex = nextIndex;
			}
		}


		_data[0] = _data.back();
		_data.pop_back();

		int now = 0;
		while (true)
		{
			int left = now * 2 + 1;
			int right = now * 2 + 2;

			if(left >= _data.size()) break;

			int next = now;

			if (_data[left] > _data[next]) next = left;
			if (right < _data.size() && _data[next] < _data[right])
				next = right;

			if(next == now) break;

			swap(_data[now], _data[next]);
			now = next;


		}
	}

	bool empty()
	{
		return _data.empty();
	}

private:
	Container _data;

};
