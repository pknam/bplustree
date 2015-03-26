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
		// 모든 node 돌면서 delete
	}

	void insert(int data, int addr);

private:
	void insertInLeaf(BPlusTreeNode* leaf, int data, int addr);
	void insertInParent(BPlusTreeNode* leaf1, int data, BPlusTreeNode* leaf2);
	BPlusTreeNode* findNode(int data);
};