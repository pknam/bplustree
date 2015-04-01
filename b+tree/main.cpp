#include <iostream>
#include "BPlusTree.h"

using namespace std;

int main()
{
	BPlusTree bptree(4);

	bptree.insert(3, 0);
	bptree.insert(2, 1);
	bptree.insert(8, 2);
	bptree.insert(4, 3);
	bptree.insert(7, 4);
	bptree.insert(1, 5);
	bptree.insert(5, 6);
	bptree.insert(9, 7);
	bptree.insert(6, 8);
	bptree.insert(10, 9);
	bptree.insert(0, 10);


	cout << "sdfsdf" << endl;

	return 0;
}