#pragma once
#include "BPlusTreeNode.h"

class BPlusTree
{
private:
	BPlusTreeNode* root;
	int n;

public:
	BPlusTree(int _n)
		: n(_n), root(nullptr)
	{}

	~BPlusTree()
	{
		delete root;
	}

	void insert(int data, int addr);

private:	// utility methods
	void insertInLeaf(BPlusTreeNode* leaf, int data, int* addr);
	void insertInParent(BPlusTreeNode* leaf1, int data, BPlusTreeNode* leaf2);
	BPlusTreeNode* findNode(int data);
};