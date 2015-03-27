#include "BPlusTree.h"
#include "BPlusTreeNode.h"

void BPlusTree::insert(int data, int addr)
{
	// if tree is empty
	if (root == nullptr)
	{
		BPlusTreeNode* tmp = new BPlusTreeNode(n, BPlusTreeNode::NodeType::LEAF);
		tmp->setData(0, data);
		tmp->setAddr(0, addr);
		tmp->setDataLength(1);

		root = tmp;
		return;
	}

	BPlusTreeNode* leaf = findNode(data);
	if (leaf->getDataLength() < n - 1)
	{
		insertInLeaf(leaf, data, addr);
	}
	else // need to split leaf
	{
		// right side of leaf
		BPlusTreeNode* newleaf = new BPlusTreeNode(n, BPlusTreeNode::NodeType::LEAF);

		// copy (n/2) ~ n
		for (int i = n / 2, j = 0; i < n; i++, j++)
		{
			newleaf->setData(j, leaf->getData(i));
			newleaf->setAddr(j, leaf->getAddr(i));
		}

		// set data length
		leaf->setDataLength(n / 2);
		newleaf->setDataLength(n - n / 2);

		// insert new data
		if (data < newleaf->getData(0))
			insertInLeaf(leaf, data, addr);
		else
			insertInLeaf(newleaf, data, addr);

		// connect links
		newleaf->setChild(n - 1, leaf->getChild(n - 1));
		leaf->setChild(n - 1, newleaf);

		insertInParent(leaf, newleaf->getData(0), newleaf);
	}
}

void BPlusTree::insertInLeaf(BPlusTreeNode* leaf, int data, int addr)
{
	int index = 0;
	while (leaf->getData(index) < data && index < leaf->getDataLength())
		index++;

	for (int i = leaf->getDataLength(); i > index; i--)
	{
		leaf->setData(i, leaf->getData(i - 1));
		leaf->setAddr(i, leaf->getAddr(i - 1));
	}

	leaf->setData(index, data);
	leaf->setAddr(index, addr);
	leaf->setDataLength(leaf->getDataLength() + 1);
}

void BPlusTree::insertInParent(BPlusTreeNode* leaf1, int data, BPlusTreeNode* leaf2)
{
	// implementing
}

BPlusTreeNode* BPlusTree::findNode(int data)
{
	BPlusTreeNode* result;

	if (root == nullptr)
		return nullptr;
	else
		result = root;

	while (result->getType() != BPlusTreeNode::NodeType::LEAF)
	{
		int next_child_index = 0;
		for (int i = 0; i < result->getDataLength(); i++)
		{
			if (result->getData(i) > data)
			{
				next_child_index = i;
			}
			else
			{
				next_child_index = i + 1;
				break;
			}
		}
		
		result = result->getChild(next_child_index);
	}


	return result;
}