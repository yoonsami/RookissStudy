#pragma once

template <typename T>
class Node
{
public:
	Node() {}
	Node(const T& value)
	{
		_data = value;
	}
	~Node() {}

public:
	Node* _next = nullptr;
	Node* _prev = nullptr;
	T _data = T();
};