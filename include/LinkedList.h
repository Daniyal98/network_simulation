#pragma once
#include <iostream>
using namespace std;
#include <string>

class RoutingTableLL
{
public:
	string machine;
	string router;
	RoutingTableLL *next;
	RoutingTableLL() {}
	RoutingTableLL(string mname, string rname)
	{
		machine = mname;
		router = rname;
	}
};

class LinkedListRT
{
public:
	RoutingTableLL * Head;
	LinkedListRT();
	RoutingTableLL* Insert(string mname, string rname, int = 0);
	void Display();
	string Search(string);
};

LinkedListRT::LinkedListRT()
{
	Head = NULL;
}

RoutingTableLL* LinkedListRT::Insert(string mname, string rname, int index) {
	if (index < 0)
		return NULL;
	int currIndex = 1;
	RoutingTableLL* currNode = Head;
	while (currNode && index > currIndex)
	{
		currNode = currNode->next;
		currIndex++;
	}
	if (index > 0 && currNode == NULL)
		return NULL;
	RoutingTableLL* newNode = new RoutingTableLL(mname, rname);

	if (index == 0)
	{
		newNode->next = Head;
		Head = newNode;
	}
	else
	{
		newNode->next = currNode->next;
		currNode->next = newNode;
	}
	return newNode;

}

void LinkedListRT::Display()
{
	RoutingTableLL *CurrNode = Head;
	while (CurrNode != NULL)
	{
		cout << CurrNode->router << " " << CurrNode->machine << endl;
		CurrNode = CurrNode->next;
	}
	cout << endl;
}

string LinkedListRT::Search(string M)
{
	RoutingTableLL *CurrNode = Head;
	int i = 1;
	while (CurrNode != NULL)
	{
		if (CurrNode->machine == M)
		{
			cout << "Found" << endl;
			return CurrNode->router;
			break;
		}
		cout << i << " ";
		i++;
		CurrNode = CurrNode->next;
	}
}