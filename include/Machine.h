#pragma once
#include <iostream>
using namespace std;
class Machine
{
public:
	string address;
	string router;
	string currenttext;
	int key;
	Machine();
	void operator=(Machine);
	Machine(string, string, int);
};

Machine::Machine()
{
	address = "";
	key = 0;
	router = "";
}

Machine::Machine(string m, string r, int k)
{
	address = m;
	router = r;
	key = k;
}

void Machine::operator=(Machine M)
{
	address = M.address;
	router = M.address;
	key = M.key;
}

