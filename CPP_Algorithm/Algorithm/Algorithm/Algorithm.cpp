
#include <iostream>
#include "MyTree.h"
int main()
{
	MyTree t;
	NodeRef root = t.CreateTree();
	t.PrintTree(root, 0);
	int height = t.GetHeight(root);
}