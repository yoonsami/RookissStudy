#pragma once
#include <string>
#include <vector>
#include <memory>
using namespace std;

using NodeRef = shared_ptr<struct Node>;

struct Node
{
	Node() { _data = ""; }
	Node(const string& data) { _data = data; }
	string _data;
	vector<NodeRef> _children;

};


class MyTree
{
public:
	NodeRef CreateTree();
	void PrintTree(NodeRef root, int depth);
	int GetHeight(NodeRef root);
};

NodeRef MyTree::CreateTree()
{
	NodeRef root = make_shared<Node>("R1 개발실");
	{
		NodeRef node = make_shared<Node>("디자인팀");
		root->_children.push_back(node);
		{
			NodeRef leaf = make_shared<Node>("전투");
			node->_children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node>("경제");
			node->_children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node>("스토리");
			node->_children.push_back(leaf);
		}
	}
	{
		NodeRef node = make_shared<Node>("프로그래밍팀");
		root->_children.push_back(node);
		{
			NodeRef leaf = make_shared<Node>("서버");
			node->_children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node>("클라");
			node->_children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node>("엔진");
			node->_children.push_back(leaf);
		}
	}
	{
		NodeRef node = make_shared<Node>("아트");
		root->_children.push_back(node);
		{
			NodeRef leaf = make_shared<Node>("배경");
			node->_children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node>("캐릭터");
			node->_children.push_back(leaf);
		}
	}
	return root;
}

void MyTree::PrintTree(NodeRef root, int depth)
{
	for (int i = 0; i < depth; ++i)
	{
		cout << "-";
	}

	cout << root->_data << endl;

	for (auto& children : root->_children)
	{
		PrintTree(children, depth + 1);
	}
}

inline int MyTree::GetHeight(NodeRef root)
{
	int height = 1;

	for (NodeRef& child : root->_children)
	{
		height = max(height, GetHeight(child) + 1);
	}
	
	return height;
	
}
