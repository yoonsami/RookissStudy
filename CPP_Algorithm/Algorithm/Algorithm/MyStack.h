#pragma once



template <typename T>
class MyStack
{


public:
	void push(const T& data)
	{
		_container.push_back(data);
	}
	T& top()
	{
		return _container.back();
	}
	void pop()
	{
		_container.pop_back();
	}


	bool empty() { return _container.empty(); }
	int size() { return _container.size(); }

private:
	vector<T> _container;
	//list<T> _container;
};