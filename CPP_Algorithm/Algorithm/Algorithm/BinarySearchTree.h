#pragma once

enum class Color
{
	Red = 0,
	Black = 1,
};

struct BSTNode
{
	BSTNode* parent = nullptr;
	BSTNode* left = nullptr;
	BSTNode* right = nullptr;
	int key = {};
};

class BinarySearchTree
{
	
public:
	void Print() { Print(_root, 10, 0); }
	void Print(BSTNode* node, int x, int y);
	void Print_InOrder() { Print_InOrder(_root); }
	void Print_InOrder(BSTNode* node);

	BSTNode* search(BSTNode* node, int key);
	BSTNode* search2(BSTNode* node, int key);

	BSTNode* Min(BSTNode* node);
	BSTNode* Max(BSTNode* node);
	BSTNode* Next(BSTNode* node);

	void insert(int key);
	void Delete(int key);
	void Delete(BSTNode* node);

	void Replace(BSTNode* u, BSTNode* v);

private:
	BSTNode* _root = nullptr;
};

