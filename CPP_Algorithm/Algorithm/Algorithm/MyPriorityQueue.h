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
	T& top()
	{
		return _data[0];
	}
	void pop()
	{
		_data[0] = _data.back();
		_data.pop_back();

		int nowIndex = 0;
		while (true)
		{
			int leftChildIndex = 2 * nowIndex + 1;
			int rightChildIndex = 2 * nowIndex + 2;

			if(leftChildIndex >= _data.size())
				break;

			int nextIndex = nowIndex;

			if (_data[leftChildIndex] > _data[nextIndex])
				nextIndex = leftChildIndex;

			if (rightChildIndex < _data.size() && _data[nextIndex] < _data[rightChildIndex])
				nextIndex = rightChildIndex;

			if(nextIndex == nowIndex)
				break;

			::swap(_data[nowIndex], _data[nextIndex]);
			nowIndex = nextIndex;
		}
	}

	bool empty()
	{
		return _data.empty();
	}

private:
	Container _data;

};
