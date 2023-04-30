#pragma once
#include<iostream>
#include<fstream>
#include <vector>
#include <string>
#include<sstream>
#include "Heap.h"
#include "Queue.h"
#include "Machine.h"
#include "LinkedList.h"
#include "Message.h"
#include "BTree.h"
#include "SplayTree.h"
using namespace std;

class Router
{
public:
	string address;
	Heap<Message> IncomingQueue;
	Queue<Message> OutgoingQueue;
	Router *NextRouter;
	int nRouter;
	Machine Machines[15];
	int numMachine;

	LinkedListRT rtlinkedlist;
	BTree rtbtree;
	SplayTreeNode *root;
	string getDestinationLL(string);
	string getDestinationBT(string);
	string getDestinationST(Machine);
	Router();
	Router(string);
	void InsertMachine(string);
	bool operator==(Router);
	void operator=(Router);
	void InsertMachine(Machine);
	void DisplayMachine();
	void makeRoutingTable(Machine, string);
};

string Router::getDestinationLL(string mname)
{
	return rtlinkedlist.Search(mname);
}
string Router::getDestinationBT(string M)
{
	return rtbtree.search(M);
}
string Router::getDestinationST(Machine M)
{
	Search(M, root);
	return root->router;
}



void Router::makeRoutingTable(Machine M, string R)
{
	//LinkedList
	rtlinkedlist.Insert(M.address, R);

	//B-Tree
	rtbtree.insert(BtreeKey(M, R));

	Insert(M, R, root);
}

void Router::DisplayMachine() {
	for (int i = 0; i < numMachine; ++i)
	{
		cout << Machines[i].address << " ";
	}
}


void Router::InsertMachine(string M) {
	Machines[numMachine].address = M;
	numMachine++;
}


Router::Router()
{
	address = "";
	NextRouter = NULL;
	numMachine = 0;
	nRouter = 0;
	rtbtree.t = 2;
	root = NULL;
}
Router::Router(string R)
{
	address = R;
	NextRouter = NULL;
	numMachine = 0;
	nRouter = 0;
	rtbtree.t = 2;
	root = NULL;
}