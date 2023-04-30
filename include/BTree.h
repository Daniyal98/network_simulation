#pragma once
#include <iostream>
using namespace std;
#include "Machine.h"
#include <string>
class BtreeKey
{
public:
	Machine machine;
	string router;
	BtreeKey()
	{
		router = "";
	}

	BtreeKey(Machine M, string rname)
	{
		machine = M;
		router = rname;
	}

	void operator=(BtreeKey B)
	{
		machine = B.machine;
		router = B.router;
	}
};

class BTreeNode
{
public:
	BtreeKey * Keys;
	BTreeNode **Child;
	int t;		//Minimum Degree
	int n;		// Current Number of Keys
	bool leaf;	//returns true if the node is leaf and false if the node is not a leaf
	BTreeNode(int _t, bool _leaf);   // Constructor

									 // A utility function to insert a new key in the subtree rooted with
									 // this node. The assumption is, the node must be non-full when this
									 // function is called
	void insertNonFull(Machine, string);

	// A utility function to split the child y of this node. i is index of y in
	// child array C[].  The Child y must be full when this function is called
	void splitChild(int i, BTreeNode *y);

	// A function to traverse all nodes in a subtree rooted with this node
	void traverse();

	// A function to search a key in subtree rooted with this node.
	string search(string);   // returns NULL if k is not present.
};

// Constructor for BTreeNode class
BTreeNode::BTreeNode(int t1, bool leaf1)
{
	// Copy the given minimum degree and leaf property
	t = t1;
	leaf = leaf1;

	// Allocate memory for maximum number of possible keys
	// and child pointers
	Keys = new BtreeKey[2 * t - 1];
	Child = new BTreeNode *[2 * t];

	// Initialize the number of keys as 0
	n = 0;
}

// A utility function to insert a new key in this node
// The assumption is, the node must be non-full when this
// function is called
void BTreeNode::insertNonFull(Machine M, string rname)
{
	// Initialize index as index of rightmost element
	int i = n - 1;

	// If this is a leaf node
	if (leaf == true)
	{
		// The following loop does two things
		// a) Finds the location of new key to be inserted
		// b) Moves all greater keys to one place ahead
		while (i >= 0 && Keys[i].machine.key > M.key)
		{
			Keys[i + 1] = Keys[i];
			i--;
		}

		// Insert the new key at found location
		Keys[i + 1].machine = M;
		Keys[i + 1].router = rname;
		n = n + 1;
	}
	else // If this node is not leaf
	{
		// Find the child which is going to have the new key
		while (i >= 0 && Keys[i].machine.key > M.key)
			i--;

		// See if the found child is full
		if (Child[i + 1]->n == 2 * t - 1)
		{
			// If the child is full, then split it
			splitChild(i + 1, Child[i + 1]);

			// After split, the middle key of C[i] goes up and
			// C[i] is splitted into two.  See which of the two
			// is going to have the new key
			if (Keys[i + 1].machine.key < M.key)
				i++;
		}
		Child[i + 1]->insertNonFull(M, rname);
	}
}

// A utility function to split the child y of this node
// Note that y must be full when this function is called
void BTreeNode::splitChild(int i, BTreeNode *y)
{
	// Create a new node which is going to store (t-1) keys
	// of y
	BTreeNode *z = new BTreeNode(y->t, y->leaf);
	z->n = t - 1;

	// Copy the last (t-1) keys of y to z
	for (int j = 0; j < t - 1; j++)
	{
		z->Keys[j].machine = y->Keys[j + t].machine;
		z->Keys[j].router = y->Keys[j + t].router;
	}


	// Copy the last t children of y to z
	if (y->leaf == false)
	{
		for (int j = 0; j < t; j++)
			z->Child[j] = y->Child[j + t];
	}

	// Reduce the number of keys in y
	y->n = t - 1;

	// Since this node is going to have a new child,
	// create space of new child
	for (int j = n; j >= i + 1; j--)
		Child[j + 1] = Child[j];

	// Link the new child to this node
	Child[i + 1] = z;

	// A key of y will move to this node. Find location of
	// new key and move all greater keys one space ahead
	for (int j = n - 1; j >= i; j--)
		Keys[j + 1] = Keys[j];

	// Copy the middle key of y to this node
	Keys[i] = y->Keys[t - 1];

	// Increment count of keys in this node
	n = n + 1;
}

// Function to search key k in subtree rooted with this node
string BTreeNode::search(string M)
{
	// Find the first key greater than or equal to k
	int i;
	for (i = 0; i < n; i++)
	{
		// If this is not leaf, then before printing key[i],
		// traverse the subtree rooted with child C[i].
		if (Keys[i].machine.address == M)
			return Keys[i].router;
		//cout << " " << Keys[i].router <<endl;
	}

	if (leaf == true)
		return "";

	// Print the subtree rooted with last child
	return Child[i]->search(M);

}

// Function to traverse all nodes in a subtree rooted with this node
void BTreeNode::traverse()
{
	// There are n keys and n+1 children, travers through n keys
	// and first n children
	int i;
	for (i = 0; i < n; i++)
	{
		// If this is not leaf, then before printing key[i],
		// traverse the subtree rooted with child C[i].
		if (leaf == false)
			Child[i]->traverse();

		cout << " " << Keys[i].router << " " << Keys[i].machine.address << endl;
	}

	// Print the subtree rooted with last child
	if (leaf == false)
		Child[i]->traverse();
}

class BTree
{
public:
	BTreeNode * root; // Pointer to root node
	int t;  // Minimum degree
			// Constructor (Initializes tree as empty)
	BTree()
	{
		root = NULL;
	}
	BTree(int _t)
	{
		root = NULL;
		t = _t;
	}

	// function to traverse the tree
	void traverse()
	{
		if (root != NULL)
			root->traverse();
	}

	// function to search a key in this tree
	string search(string M)
	{
		return root->search(M);
	}

	// The main function that inserts a new key in this B-Tree
	void insert(BtreeKey);
};

// The main function that inserts a new key in this B-Tree
void BTree::insert(BtreeKey k)
{
	// If tree is empty
	if (root == NULL)
	{
		// Allocate memory for root
		root = new BTreeNode(t, true);
		root->Keys[0] = k;  // Insert key
		root->n = 1;  // Update number of keys in root
	}
	else // If tree is not empty
	{
		// If root is full, then tree grows in height
		if (root->n == 2 * t - 1)
		{
			// Allocate memory for new root
			BTreeNode *s = new BTreeNode(t, false);

			// Make old root as child of new root
			s->Child[0] = root;

			// Split the old root and move 1 key to the new root
			s->splitChild(0, root);

			// New root has two children now.  Decide which of the
			// two children is going to have new key
			int i = 0;
			if (s->Keys[0].machine.key < k.machine.key)
				i++;
			s->Child[i]->insertNonFull(k.machine, k.router);

			// Change root
			root = s;
		}
		else  // If root is not full, call insertNonFull for root
			root->insertNonFull(k.machine, k.router);
	}
}