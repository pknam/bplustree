#include <iostream>
#include "BPlusTree.h"

using namespace std;

int main()
{
	BPlusTree bptree(4);

	bptree.insert(1, 10);
	bptree.insert(2, 4);
	bptree.insert(4, 8);
	//bptree.insert()

	cout << "sdfsdf" << endl;

	return 0;
}