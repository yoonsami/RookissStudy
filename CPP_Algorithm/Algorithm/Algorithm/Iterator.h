#pragma once
#include "Node.h"

template<typename T>
class MyIterator
{
public:
	MyIterator() {}
	MyIterator(Node<T>* node)
	{
		_node = node;
	}
	~MyIterator() {}

	MyIterator& operator++()
	{
		_node = _node->_next;
		return *this;
	}

	MyIterator operator++(int)
	{
		MyIterator tmp = *this;
		_node = _node->_next;
		return tmp;
	}

	MyIterator& operator--()
	{
		_node = _node->_prev;
		return *this;
	}

	MyIterator operator--(int)
	{
		MyIterator tmp = *this;
		_node = _node->_prev;
		return tmp;
	}

	T& operator*()
	{
		return _node->_data;
	}

	bool operator==(const MyIterator& iter)
	{
		return _node == iter._node;
	}
	bool operator!=(const MyIterator& iter)
	{
		return _node != iter._node;
	}

public:
	Node<T>* _node = nullptr;
};
