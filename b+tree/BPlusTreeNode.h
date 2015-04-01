#pragma once

class BPlusTreeNode
{
public:
	enum NodeType
	{
		INNER,
		LEAF
	};

private:
	NodeType type;

	// max size of node
	int n;

	// pointer of parent
	BPlusTreeNode* parent;

	// data array
	int* data;

	// array of child pointer
	// ONLY used in inner node
	BPlusTreeNode** children;

	// ONLY used in leaf node
	int** addr;

	// ONLY used in leaf node
	BPlusTreeNode* nextLeafNode;

	// number of data in this node
	int dataLength;

public:
	BPlusTreeNode(int _n, NodeType _type)
		: n(_n), type(_type), dataLength(0)
	{
		if (_type == NodeType::LEAF)
			addr = new int*[_n - 1];
		else
			children = new BPlusTreeNode*[_n];

		data = new int[_n - 1];

	}

	~BPlusTreeNode()
	{
		delete[] data;

		if (type == NodeType::LEAF)
			delete[] addr;
		else
		{
			// except temporary node
			if (dataLength > 0)
			{
				for (int i = 0; i < dataLength + 1; i++)
					delete children[i];
			}

			delete[] children;
		}
	}

public:
	NodeType getType();

	BPlusTreeNode* getParent();
	void setParent(BPlusTreeNode* node);

	BPlusTreeNode* getChild(int index);
	void setChild(int index, BPlusTreeNode* node);

	int getData(int index);
	void setData(int index, int data);

	int* getAddr(int index);
	void setAddr(int index, int* addr);

	int getDataLength();
	void setDataLength(int length);

	BPlusTreeNode* getNextLeafNode();
	void setNextLeafNode(BPlusTreeNode* node);
};