#include "BPlusTree.h"
#include "BPlusTreeNode.h"

void BPlusTree::insert(int data, int addr)
{
	// if tree is empty
	if (root == nullptr)
	{
		BPlusTreeNode* tmp = new BPlusTreeNode(n, BPlusTreeNode::NodeType::LEAF);
		tmp->setData(0, data);
		tmp->setAddr(0, (int*) addr);
		tmp->setDataLength(1);

		root = tmp;
		return;
	}

	BPlusTreeNode* leaf = findNode(data);
	if (leaf->getDataLength() < n - 1)
	{
		insertInLeaf(leaf, data, (int*) addr);
	}
	else // need to split leaf
	{
		// right side of leaf
		BPlusTreeNode* newleaf = new BPlusTreeNode(n, BPlusTreeNode::NodeType::LEAF);
		BPlusTreeNode tmp(n + 1, BPlusTreeNode::NodeType::LEAF);

		insertInLeaf(&tmp, data, (int*) addr);
		for (int i = 0; i < n - 1; i++)
			insertInLeaf(&tmp, leaf->getData(i), leaf->getAddr(i));

		leaf->setDataLength(0);
		newleaf->setDataLength(0);

		for (int i = 0; i < n; i++)
		{
			if (i < n / 2)
			{
				insertInLeaf(leaf, tmp.getData(i), tmp.getAddr(i));
			}
			else
			{
				insertInLeaf(newleaf, tmp.getData(i), tmp.getAddr(i));
			}
		}

		// connect links
		//newleaf->setChild(n - 1, leaf->getChild(n - 1));
		newleaf->setNextLeafNode(leaf->getNextLeafNode());
		//leaf->setChild(n - 1, newleaf);
		leaf->setNextLeafNode(newleaf);

		insertInParent(leaf, newleaf->getData(0), newleaf);
	}
}

void BPlusTree::insertInLeaf(BPlusTreeNode* leaf, int data, int* addr)
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
	leaf->setAddr(index, (int*) addr);
	leaf->setDataLength(leaf->getDataLength() + 1);
}

void BPlusTree::insertInParent(BPlusTreeNode* leaf, int data, BPlusTreeNode* newleaf)
{
	if (leaf == root)
	{
		BPlusTreeNode* tmp = new BPlusTreeNode(n, BPlusTreeNode::NodeType::INNER);
		tmp->setData(0, data);
		tmp->setChild(0, leaf);
		tmp->setChild(1, newleaf);
		tmp->setDataLength(1);

		leaf->setParent(tmp);
		newleaf->setParent(tmp);

		root = tmp;

		return;
	}

	BPlusTreeNode* parent = leaf->getParent();
	if (parent->getDataLength() < n - 1)
	{
		int index = 0;
		while (parent->getData(index) < data && index < parent->getDataLength())
			index++;

		parent->setData(index, data);
		parent->setChild(index + 1, newleaf);
		parent->setDataLength(parent->getDataLength() + 1);

		newleaf->setParent(parent);
	}
	else // split parent
	{
		// right side of parent
		BPlusTreeNode tmp(n + 1, BPlusTreeNode::NodeType::INNER);
		bool inserted = false;

		tmp.setChild(0, parent->getChild(0));
		for (int i = 0, j = 0; i < n; i++)
		{
			// i : index of tmp
			// j : index of parent

			if (parent->getData(j) > data && !inserted)
			{
				tmp.setData(i, data);
				tmp.setChild(i + 1, newleaf);
				inserted = true;
			}
			else
			{
				tmp.setData(i, parent->getData(j));
				tmp.setChild(i + 1, parent->getChild(j + 1));
				j++;
			}
		}


		BPlusTreeNode* newparent = new BPlusTreeNode(n, BPlusTreeNode::NodeType::INNER);

		parent->setChild(0, tmp.getChild(0));
		for (int i = 0, j = 0; i < n; i++)
		{
			if (i < n / 2)
			{
				parent->setData(i, tmp.getData(i));
				parent->setChild(i + 1, tmp.getChild(i + 1));
			}
			else if (i == n / 2)
			{
				newparent->setChild(j, tmp.getChild(i + 1));
			}
			else if (i > n / 2)
			{
				newparent->setData(j, tmp.getData(i));
				newparent->setChild(j + 1, tmp.getChild(i + 1));
				j++;
			}
		}

		parent->setDataLength(n / 2);
		newparent->setDataLength(n - n / 2 - 1);

		for (int i = 0; i < newparent->getDataLength() + 1; i++)
			newparent->getChild(i)->setParent(newparent);


		insertInParent(parent, tmp.getData(n / 2), newparent);
	}
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
		int index = 0;
		while (result->getData(index) < data && index < result->getDataLength())
			index++;

		result = result->getChild(index);
	}


	return result;
}