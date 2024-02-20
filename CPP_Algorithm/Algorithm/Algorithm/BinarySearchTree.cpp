#include "BinarySearchTree.h"
#include <iostream>
#include <windows.h>
using namespace std;

void SetCursorPosition(int x, int y)
{
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { static_cast<SHORT>(x),static_cast<SHORT>(y) };
	::SetConsoleCursorPosition(output, pos);
}

void BinarySearchTree::Print(BSTNode* node, int x, int y)
{
	if (node == nullptr) return;

	SetCursorPosition(x, y);

	cout << node->key;
	Print(node->left, x - (5 / (y + 1)), y + 1);
	Print(node->right, x + (5 / (y + 1)), y + 1);
}
void BinarySearchTree::Print_InOrder(BSTNode* node)
{
	if (node == nullptr) return;
	// 전위 순회 preorder traverse
	// 중위 순회 inorder
	// 후위 순회 postorder


	//중
	Print_InOrder(node->left);
	cout << node->key << endl;
	Print_InOrder(node->right);
}

BSTNode* BinarySearchTree::search(BSTNode* node, int key)
{
	if (!node || key == node->key) return node;

	if (key < node->key) return search(node->left, key);
	else return search(node->right, key);

}

BSTNode* BinarySearchTree::search2(BSTNode* node, int key)
{
	while (node && key != node->key)
	{
		if (key < node->key)
			node = node->left;
		else
			node = node->right;
	}
	return node;
}

BSTNode* BinarySearchTree::Min(BSTNode* node)
{
	if (!node) return node;

	while (node->left)
		node = node->left;

	return node;
}

BSTNode* BinarySearchTree::Max(BSTNode* node)
{
	if (!node) return node;

	while (node->right)
		node = node->right;

	return node;
}

BSTNode* BinarySearchTree::Next(BSTNode* node)
{
	if (!node) return node;

	if (node->right) return Min(node->right);

	BSTNode* parent = node->parent;

	while (parent && parent->right == node)
	{
		node = parent;
		parent = parent->parent;
	}
	return parent;
}

void BinarySearchTree::insert(int key)
{
	BSTNode* newNode = new BSTNode;
	newNode->key = key;

	if (!_root)
	{
		_root = newNode;
		return;
	}

	BSTNode* node = _root;
	BSTNode* parent = nullptr;

	while (node)
	{
		parent = node;

		if (node->key > key)
			node = node->left;
		else
			node = node->right;
	}

	newNode->parent = parent;
	if (parent->key > key)
		parent->left = newNode;
	else
		parent->right = newNode;
}

void BinarySearchTree::Delete(int key)
{
	BSTNode* deleteNode = search2(_root, key);
	Delete(deleteNode);
}

void BinarySearchTree::Delete(BSTNode* node)
{
	if (!node) return;

	if (!node->left)
		Replace(node, node->right);
	else if (!node->right)
		Replace(node, node->left);
	else
	{
		BSTNode* next = Next(node);
		node->key = next->key;
		Delete(next);
	}
}

void BinarySearchTree::Replace(BSTNode* u, BSTNode* v)
{
	if (!u->parent) _root = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;

	if (v)
		v->parent = u->parent;

	delete u;
}
