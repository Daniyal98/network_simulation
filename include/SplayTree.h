#pragma once
#include <iostream>
using namespace std;
#include <string>
#include "Machine.h"


class SplayTreeNode
{
public:
	Machine machine;
	string router;
	SplayTreeNode *leftChild;
	SplayTreeNode *rightChild;
	SplayTreeNode()
	{
		router = "";
	}

	SplayTreeNode(Machine M, string rname)
	{
		machine = M;
		router = rname;
	}
};

SplayTreeNode* RR_Rotate(SplayTreeNode*& k2)
{
	SplayTreeNode* k1 = k2->leftChild;
	k2->leftChild = k1->rightChild;
	k1->rightChild = k2;
	return k1;
}

// LL(Y rotates to the left)
SplayTreeNode* LL_Rotate(SplayTreeNode*& k2)
{
	SplayTreeNode* k1 = k2->rightChild;
	k2->rightChild = k1->leftChild;
	k1->leftChild = k2;
	return k1;
}

// An implementation of top-down splay tree
SplayTreeNode* Splay(Machine M, SplayTreeNode*& root)
{
	if (!root)
		return NULL;
	SplayTreeNode header;
	/* header.rchild points to L tree;
	header.lchild points to R Tree */
	header.leftChild = header.rightChild = NULL;
	SplayTreeNode* LeftTreeMax = &header;
	SplayTreeNode* RightTreeMin = &header;
	while (1)
	{
		if (M.key < root->machine.key)
		{
			if (!root->leftChild)
				break;
			if (M.key < root->leftChild->machine.key)
			{
				root = RR_Rotate(root);
				// only zig-zig mode need to rotate once,
				if (!root->leftChild)
					break;
			}
			/* Link to R Tree */
			RightTreeMin->leftChild = root;
			RightTreeMin = RightTreeMin->leftChild;
			root = root->leftChild;
			RightTreeMin->leftChild = NULL;
		}
		else if (M.key > root->machine.key)
		{
			if (!root->rightChild)
				break;
			if (M.key > root->rightChild->machine.key)
			{
				root = LL_Rotate(root);
				// only zag-zag mode need to rotate once,
				if (!root->rightChild)
					break;
			}
			/* Link to L Tree */
			LeftTreeMax->rightChild = root;
			LeftTreeMax = LeftTreeMax->rightChild;
			root = root->rightChild;
			LeftTreeMax->rightChild = NULL;
		}
		else
			break;
	}
	/* assemble L Tree, Middle Tree and R tree */
	LeftTreeMax->rightChild = root->leftChild;
	RightTreeMin->leftChild = root->rightChild;
	root->leftChild = header.rightChild;
	root->rightChild = header.leftChild;
	return root;
}

SplayTreeNode* New_Node(Machine M, string rname)
{
	SplayTreeNode* p_node = new SplayTreeNode;
	if (!p_node)
	{
		fprintf(stderr, "Out of memory!\n");
		exit(1);
	}
	p_node->machine = M;
	p_node->router = rname;
	p_node->leftChild = p_node->rightChild = NULL;
	return p_node;
}

SplayTreeNode* Insert(Machine M, string rname, SplayTreeNode*& root)
{
	SplayTreeNode* p_node = NULL;
	if (!p_node)
		p_node = New_Node(M, rname);
	else
	{
		p_node->machine = M;
		p_node->router = rname;
	}
	if (!root)
	{
		root = p_node;
		p_node = NULL;
		return root;
	}
	root = Splay(M, root);
	/* This is BST that, all keys <= root->key is in root->lchild, all keys >
	root->key is in root->rchild. */
	if (M.key <= root->machine.key)
	{
		p_node->leftChild = root->leftChild;
		p_node->rightChild = root;
		root->leftChild = NULL;
		root = p_node;
	}
	else if (M.key > root->machine.key)
	{
		p_node->rightChild = root->rightChild;
		p_node->leftChild = root;
		root->rightChild = NULL;
		root = p_node;
	}
	else
		return root;
	p_node = NULL;
	return root;
}

/*splay* Delete(int key, splay* root)
{
splay* temp;
if (!root)
return NULL;
root = Splay(key, root);
if (key != root->key)
return root;
else
{
if (!root->lchild)
{
temp = root;
root = root->rchild;
}
else
{
temp = root;
/*Note: Since key == root->key,
so after Splay(key, root->lchild),
the tree we get will have no right child tree.
root = Splay(key, root->lchild);
root->rchild = temp->rchild;
}
free(temp);
return root;
}
}*/

SplayTreeNode* Search(Machine M, SplayTreeNode* root)
{
	return Splay(M, root);
}

void InOrder(SplayTreeNode* root)
{
	if (root)
	{
		InOrder(root->leftChild);
		cout << "key: " << root->machine.address << " " << root->router;
		if (root->leftChild)
			cout << " | left child: " << root->leftChild->machine.address << root->leftChild->router;
		if (root->rightChild)
			cout << " | right child: " << root->rightChild->machine.address << root->rightChild->router;
		cout << "\n";
		InOrder(root->rightChild);
	}
}