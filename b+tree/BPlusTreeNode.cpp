#include "BPlusTreeNode.h"

BPlusTreeNode::NodeType BPlusTreeNode::getType()
{
	return type;
}

BPlusTreeNode* BPlusTreeNode::getParent()
{
	return parent;
}

void BPlusTreeNode::setParent(BPlusTreeNode* node)
{
	parent = node;
}

BPlusTreeNode* BPlusTreeNode::getChild(int index)
{
	return children[index];
}

void BPlusTreeNode::setChild(int index, BPlusTreeNode* node)
{
	children[index] = node;
}

int BPlusTreeNode::getData(int index)
{
	return data[index];
}

void BPlusTreeNode::setData(int index, int data)
{
	this->data[index] = data;
}

void BPlusTreeNode::removeData(int index)
{
	// implementing
}

int BPlusTreeNode::getDataLength()
{
	return dataLength;
}

void BPlusTreeNode::setDataLength(int length)
{
	dataLength = length;
}

int BPlusTreeNode::getAddr(int index)
{
	return addr[index];
}

void BPlusTreeNode::setAddr(int index, int addr)
{
	this->addr[index] = addr;
}

void BPlusTreeNode::removeAddr(int index)
{
	// implementing
}