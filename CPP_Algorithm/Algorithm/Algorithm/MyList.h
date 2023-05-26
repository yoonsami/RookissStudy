#pragma once

#include "Iterator.h"


template<typename T>
class MyList
{
public:
	MyList() : _size(0)
	{
		_head = new Node<T>();
		_tail = new Node<T>();
		_head->_next = _tail;
		_tail->_prev = _head;
	}
	~MyList()
	{
		while (_size>0)
		{
			pop_back();
		}
		delete _head;
		delete _tail;
	}

public:
	void push_back(const T& value)
	{
		AddNode(_tail, value);
	}

	void push_front(const T& value)
	{
		Node<T>* beforeNode = _head->_next;
		AddNode(beforeNode, value);
	}

	void pop_back()
	{
		Node<T>* targetNode = _tail->_prev;
		if (targetNode == _head)
			return;
		RemoveNode(targetNode);
	}

	void pop_front()
	{
		Node<T>* targetNode = _head->_next;
		if (targetNode == _tail)
			return;

		RemoveNode(targetNode);
	}


public:
	// head prevnode			before .... tail
	// head prevnode newnode	before .... tail
	Node<T>* AddNode(Node<T>* before, const T& value)
	{
		Node<T>* newNode = new Node<T>(value);
		Node<T>* prevNode = before->_prev;

		prevNode->_next = newNode;
		newNode->_prev = prevNode;

		newNode->_next = before;
		before->_prev = newNode;
		
		++_size;

		return newNode;
	}

	// prevNode node nextNode
	// preNode nextNode

	Node<T>* RemoveNode(Node<T>* node)
	{
		Node<T>* prevNode = node->_prev;
		Node<T>* nextNode = node->_next;

		prevNode->_next = nextNode;
		nextNode->_prev = prevNode;

		delete node;
		--_size;

		return nextNode;
	}

	int size() { return _size; }

	using iterator = MyIterator<T>;

	iterator begin()
	{
		return iterator(_head->_next);
	}
	iterator end()
	{
		return iterator(_tail);
	}

	iterator insert(const iterator& iter, const T& value)
	{
		Node<T>* node = AddNode(iter._node, value);
		return iterator(node);
	}

	iterator erase(const iterator& iter)
	{
		Node<T>* node = RemoveNode(iter._node);
		return iterator(node);
	}

public:
	Node<T>* _head;
	Node<T>* _tail;
	int		_size;
};
