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

	// array of child pointer
	// InnerNode : 
	BPlusTreeNode** children;

	// data array
	int* data;

	// ONLY used in leaf node
	int* addr;

	// number of data in this node
	int dataLength;

public:
	BPlusTreeNode(int _n, NodeType _type)
		: n(_n), type(_type), dataLength(0)
	{
		if (_type == NodeType::LEAF)
			addr = new int[_n - 1];

		data = new int[_n - 1];
		children = new BPlusTreeNode*[_n];

		for (int i = 0; i < _n; i++)
			children[i] = nullptr;
	}

	~BPlusTreeNode()
	{
		for (int i = 0; i < n; i++)
			if (children[i])
				delete children[i];

		delete[] children;
		delete[] data;

		if (type == NodeType::LEAF)
			delete[] addr;
	}

public:
	NodeType getType();

	BPlusTreeNode* getParent();
	void setParent(BPlusTreeNode* node);

	BPlusTreeNode* getChild(int index);
	void setChild(int index, BPlusTreeNode* node);

	int getData(int index);
	void setData(int index, int data);
	void removeData(int index);

	int getAddr(int index);
	void setAddr(int index, int addr);
	void removeAddr(int index);

	int getDataLength();
	void setDataLength(int length);
};