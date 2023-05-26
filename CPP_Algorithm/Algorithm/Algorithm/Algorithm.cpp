
#include <iostream>
#include <vector>
#include "MyVector.h"
#include <list>
#include "MyList.h"

using namespace std;


int main()
{
	MyList<int> li;

	MyList<int>::iterator eraseit;
	for (int i = 0; i < 10; ++i)
	{
		if (i == 5)
			eraseit = li.insert(li.end(), i);
		else
			li.push_back(i);
	}

	li.pop_back();

	li.erase(eraseit);

	for (auto it = li.begin(); it != li.end(); ++it)
		cout << (*it) << endl;
}