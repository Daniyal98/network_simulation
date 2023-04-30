#pragma once
#include <iostream>
using namespace std;

class Message
{

public:
	int id;
	int priority;
	string source;
	string destination;
	string text;
	string trace;
	Message();
	Message(string tex)
	{
		tex = tex;
	}
	Message(int, int, string, string, string);
	void operator=(Message &);
	//~Message();
};

Message::Message()
{
	id = 0;
	priority = 0;
	trace = "";
	text = "";
	source = "";
	destination = "";
}

Message::Message(int i, int p, string s, string d, string t)
{
	id = i;
	priority = p;
	source = s;
	destination = d;
	text = t;
}

void Message::operator=(Message &M)
{
	//id = M.id;
	priority = M.priority;
	//source = M.source;
	//destination = M.destination;
	text = M.text;
}
