#include<iostream>
#include<fstream>
#include <unistd.h>
#include <vector>
#include <string>
#include<sstream>
#include "Machine.h"
#include "Message.h"
#include "Heap.h"
#include "Queue.h"
#include "LinkedList.h"
#include "BTree.h"
#include "SplayTree.h"
#include "Router.h"
#include "MinHeap.h"
using namespace std;


int minDistance(int dist[], bool sptSet[])
{
	// Initialize min value
	int min = INT_MAX, min_index;

	for (int v = 0; v < 5; v++)
		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}

// A utility function to print the constructed distance array


void dijkstra(int **graph, int src, int *&darray, int *&par, int size)
{
	int *dist = new int[size];     // The output array.  dist[i] will hold the shortest
								   // distance from src to i

	bool *sptSet = new bool[size]; // sptSet[i] will true if vertex i is included in shortest
								   // path tree or shortest distance from src to i is finalized

								   // Initialize all distances as INFINITE and stpSet[] as false
	for (int i = 0; i < size; i++)
		dist[i] = INT_MAX, sptSet[i] = false;

	// Distance of source vertex from itself is always 0
	dist[src] = 0;

	// Find shortest path for all vertices
	for (int count = 0; count < size - 1; count++)
	{
		// Pick the minimum distance vertex from the set of vertices not
		// yet processed. u is always equal to src in first iteration.
		int u = minDistance(dist, sptSet);

		// Mark the picked vertex as processed
		sptSet[u] = true;

		// Update dist value of the adjacent vertices of the picked vertex.
		for (int v = 0; v < size; v++)
		{

			// Update dist[v] only if is not in sptSet, there is an edge from 
			// u to v, and total weight of path from src to  v through u is 
			// smaller than current value of dist[v]
			if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
			{

				dist[v] = dist[u] + graph[u][v];
				if (u != src)
				{
					par[v] = u + 1;

				}

			}
		}
	}
	for (int i = 0; i < size; i++) {
		//graph[src][i] = dist[i];
		darray[i] = dist[i];
	}


}

void FileRead(string *GraphName, int **&GraphArray, int size)
{
	string temp;
	string filename = "../network.csv";
	//cout << "Enter file name :";
	//cin >> filename;
	fstream file(filename.c_str(), ios::in);
	int a = 1;
	while (!file.eof())
	{
		getline(file, temp, ',');
		for (int i = 0; i < size - 1; i++)
			getline(file, GraphName[i], ',');
		getline(file, GraphName[size - 1], '\n');
		for (int i = 0; i < size; i++)
		{
			getline(file, temp, ',');
			for (int j = 0; j < size - 1; j++)
			{
				getline(file, temp, ',');
				if (temp == "?")
					GraphArray[i][j] = 0;
				else
				{
					stringstream geek(temp);
					geek >> GraphArray[i][j];
				}
			}
			getline(file, temp, '\n');
			if (temp == "?")
				GraphArray[i][size - 1] = 0;
			else
			{
				stringstream geek(temp);
				geek >> GraphArray[i][size - 1];
			}
		}
	}
}
void makeRouterMatrix(int **&Array, int **GraphArray, int size, int rsize)
{

	for (int i = 0, j = size - rsize; i < rsize, j < size; i++, j++)
		for (int k = 0, l = size - rsize; k < rsize, l < size; k++, l++)
			Array[i][k] = GraphArray[j][l];

}
void initialiseRM(string *GraphName, int **GraphArray, Machine *&ListM, Router *&List, int size, int rsize)
{
	for (int i = 0; i < size - rsize; i++)
		ListM[i].address = GraphName[i];

	for (int i = size - rsize; i < size; ++i)
		List[i - (size - rsize)].address = GraphName[i];

	for (int i = size - rsize; i < size; ++i)
		for (int j = 0; j < size - rsize; ++j)
			if (GraphArray[i][j] != 0)
			{
				ListM[j].router = List[i - (size - rsize)].address;
				ListM[j].key = GraphArray[i][j];
				List[i - (size - rsize)].InsertMachine(ListM[j].address);
			}
}
void routingTable(int **GraphArray, Machine *&ListM, Router *&List, int size, int rsize)
{

	for (int i = 0; i < rsize; i++)
		for (int j = 0; j < rsize; j++)
			for (int k = 0; k < size - rsize; k++)
				if (GraphArray[j + size - rsize][k] != 0)
					List[i].makeRoutingTable(ListM[k], ListM[k].router);

}
void SendText(Message Text, int **Array, Machine *ListM, Router *List, int size, int rsize)
{
	string destinationR, sourceR;
	int destinationind;
	cout << endl;
	for (int i = 0; i < size - rsize; i++)
		if (Text.destination == ListM[i].address)
			destinationind = i;

	for (int a = 0; a < size - rsize; a++)
	{
		if (Text.source == ListM[a].address)
		{
			for (int i = 0; i < rsize; i++)
			{
				if (List[i].address == ListM[a].router)
				{
					Text.trace += List[i].address;
					List[i].OutgoingQueue.enQueue(Text);
					sourceR = List[i].address;
					int opt;
					cout << "Enter 1 for LinkedList, Enter 2 for BTree, Enter 3 for SplayTree: ";
					cin >> opt;
					if (opt == 1)
						destinationR = List[i].getDestinationLL(Text.destination);
					if (opt == 2)
						destinationR = List[i].getDestinationBT(Text.destination);
					if (opt == 3)
						destinationR = List[i].getDestinationST(ListM[destinationind]);
					cout << sourceR;
					cout << destinationR << "L";
					int *dijsktralist = new int[rsize];
					int *parent = new int[rsize];
					for (int i = 0; i < rsize; i++)
						parent[i] = 0;
					dijkstra(Array, i, dijsktralist, parent, rsize);

					for (int j = 0; j < rsize; j++)
					{
						if (List[j].address == destinationR)
						{

							if (parent[j] == 0)
							{
								cout << "Press Enter to Send Text";
								system("pause");
								cout << "Message sent from '" << Text.source << "'" << endl;
								usleep(1000000);
								if (List[j].address != Text.trace)
								{
									Text.trace += "->";
									Text.trace += List[j].address;

								}
								cout << "Message recieved to '" << List[j].address << "'" << endl;
								usleep(1000000);
								List[j].IncomingQueue.Insert(Text);
								cout << "Message recieved to '" << Text.destination << "'" << endl;

								cout << "The Text '" << Text.text << "' has been delivered from '" << Text.source << "' to '" << Text.destination << "' Through "
									<< Text.trace << endl;
								break;
							}
							else
							{
								cout << "L";
								string* temp = new string[rsize];
								int ind = 0;
								int k = j;
								while (parent[k] != 0)
								{

									k = parent[k] - 1;
									temp[ind] = List[k].address;
									ind++;
									dijkstra(Array, k, dijsktralist, parent, rsize);

								}
								cout << "Press Enter to Send Text";
								system("pause");
								cout << "Message sent from '" << Text.source << "'" << endl;
								usleep(1000000);
								cout << "Message recieved at '" << ListM[a].router << "'" << endl;
								usleep(1000000);
								for (int m = ind - 1; m >= 0; m--)
								{
									Text.trace += "->";
									Text.trace += temp[m];
									cout << "Message recieved at '" << temp[m] << "'" << endl;
									usleep(1000000);
								}
								Text.trace += "->";
								Text.trace += List[j].address;
								cout << "Message recieved at '" << List[j].address << "'" << endl;
								usleep(1000000);
								List[j].IncomingQueue.Insert(Text);
								cout << "Message recieved at '" << Text.destination << "'" << endl;
								List[i].OutgoingQueue.deQueue();
								List[j].IncomingQueue.clear_heap();
								cout << "The Text '" << Text.text << "' has been delivered from '" << Text.source << "' to '" << Text.destination << "' Through "
									<< Text.trace << endl;
								break;
							}
						}
					}
				}
			}
		}
	}

}

void printPath1_1(int **Array, Machine *&ListM, Router *&List, int size, int rsize)
{

	string destinationR, sourceR, destinationM = "M13", sourceM = "M1", trace = sourceM + "->";
	int destinationind;
	cout << "Enter source machine : " << endl;
	cin >> sourceM;
	cout << "Enter destination machine : " << endl;
	cin >> destinationM;
	cout << endl;
	for (int i = 0; i < size - rsize; i++)
		if (destinationM == ListM[i].address)
			destinationind = i;
	int opt;
	cout << "Enter 1 for LinkedList, Enter 2 for BTree, Enter 3 for SplayTree: ";
	cin >> opt;
	for (int a = 0; a < size - rsize; a++)
	{
		if (sourceM == ListM[a].address)
		{
			for (int i = 0; i < rsize; i++)
			{
				if (List[i].address == ListM[a].router)
				{
					trace += List[i].address;
					sourceR = List[i].address;

					if (opt == 1)
						destinationR = List[i].getDestinationLL(destinationM);
					if (opt == 2)
						destinationR = List[i].getDestinationBT(destinationM);
					if (opt == 3)
						destinationR = List[i].getDestinationST(ListM[destinationind]);

					int *dijsktralist = new int[rsize];
					int *parent = new int[rsize];
					for (int i = 0; i < rsize; i++)
						parent[i] = 0;

					dijkstra(Array, i, dijsktralist, parent, rsize);
					for (int j = 0; j < rsize; j++)
					{
						if (List[j].address == destinationR)
						{
							if (parent[j] == 0)
							{
								if (List[j].address != trace)
								{
									trace += "->";
									trace += List[j].address;

								}
								trace += "->";
								trace += destinationM;

								cout << trace << endl;
								break;
							}
							else
							{
								string* temp = new string[rsize];
								int ind = 0;
								int k = j;
								while (parent[k] != 0)
								{
									cout << k;
									k = parent[k] - 1;
									temp[ind] = List[k].address;
									ind++;
									dijkstra(Array, k, dijsktralist, parent, rsize);

								}
								for (int m = ind - 1; m >= 0; m--)
								{
									trace += "->";
									trace += temp[m];
								}
								trace += "->";
								trace += List[j].address;
								trace += "->";
								trace += destinationM;
								cout << trace << endl;
								break;
							}
						}
					}
				}
			}
		}
	}
}
void printPath1_All(int **Array, Machine *&ListM, Router *&List, int size, int rsize)
{
	string destinationR, sourceR, sourceM = "M1", trace;;
	cout << "Enter source machine : " << endl;
	cin >> sourceM;
	int opt;
	cout << "Enter 1 for LinkedList, Enter 2 for BTree, Enter 3 for SplayTree: ";
	cin >> opt;
	for (int a = 0; a < size - rsize; a++)
	{
		if (sourceM == ListM[a].address)
		{
			for (int i = 0; i < rsize; i++)
			{
				for (int des = 0; des < size - rsize; des++)
					if (List[i].address == ListM[a].router)
					{
						trace = "";
						trace = sourceM + "->";
						trace += List[i].address;
						sourceR = List[i].address;

						if (opt == 1)
							destinationR = List[i].getDestinationLL(ListM[des].address);
						if (opt == 2)
							destinationR = List[i].getDestinationBT(ListM[des].address);
						if (opt == 3)
							destinationR = List[i].getDestinationST(ListM[des]);

						int *dijsktralist = new int[rsize];
						int *parent = new int[rsize];
						for (int i = 0; i < rsize; i++)
							parent[i] = 0;

						dijkstra(Array, i, dijsktralist, parent, rsize);
						for (int j = 0; j < rsize; j++)
						{
							if (List[j].address == destinationR)
							{
								if (parent[j] == 0)
								{
									if (ListM[a].address != ListM[j].address)
									{
										trace += "->";
										trace += List[j].address;

									}
									trace += "->";
									trace += ListM[des].address;

									cout << trace << endl;

								}
								else
								{
									string* temp = new string[rsize];
									int ind = 0;
									int k = j;
									while (parent[k] != 0)
									{
										cout << k;
										k = parent[k] - 1;
										temp[ind] = List[k].address;
										ind++;
										dijkstra(Array, k, dijsktralist, parent, rsize);

									}
									for (int m = ind - 1; m >= 0; m--)
									{
										trace += "->";
										trace += temp[m];
									}
									trace += "->";
									trace += List[j].address;
									trace += "->";
									trace += ListM[des].address;
									cout << trace << endl;

								}
							}
						}
					}
			}
		}
	}
}
void printPathAll_1(int **Array, Machine *&ListM, Router *&List, int size, int rsize)
{

	string destinationR, sourceR, destinationM = "M1", sourceM, trace;;
	cout << "Enter destination machine : " << endl;
	cin >> destinationM;
	int opt;
	cout << "Enter 1 for LinkedList, Enter 2 for BTree, Enter 3 for SplayTree: ";
	cin >> opt;
	int destinationind;
	cout << endl;
	for (int i = 0; i < size - rsize; i++)
		if (destinationM == ListM[i].address)
			destinationind = i;

	for (int a = 0; a < size - rsize; a++)
	{
		sourceM = ListM[a].address;
		{
			for (int i = 0; i < rsize; i++)
			{
				if (List[i].address == ListM[a].router)
					//for (int des = 0; des < size - rsize; des++)
				{
					trace = "";
					trace = sourceM + "->";
					trace += List[i].address;
					sourceR = List[i].address;

					if (opt == 1)
						destinationR = List[i].getDestinationLL(destinationM);
					if (opt == 2)
						destinationR = List[i].getDestinationBT(destinationM);
					if (opt == 3)
						destinationR = List[i].getDestinationST(ListM[destinationind]);

					int *dijsktralist = new int[rsize];
					int *parent = new int[rsize];
					for (int i = 0; i < rsize; i++)
						parent[i] = 0;

					dijkstra(Array, i, dijsktralist, parent, rsize);
					for (int j = 0; j < rsize; j++)
					{
						if (List[j].address == destinationR)
						{
							if (parent[j] == 0)
							{
								if (ListM[a].address != ListM[j].address)
								{
									trace += "->";
									trace += List[j].address;

								}
								trace += "->";
								trace += destinationM;

								cout << trace << endl;

							}
							else
							{
								string* temp = new string[rsize];
								int ind = 0;
								int k = j;
								while (parent[k] != 0)
								{
									cout << k;
									k = parent[k] - 1;
									temp[ind] = List[k].address;
									ind++;
									dijkstra(Array, k, dijsktralist, parent, rsize);

								}
								for (int m = ind - 1; m >= 0; m--)
								{
									trace += "->";
									trace += temp[m];
								}
								trace += "->";
								trace += List[j].address;
								trace += "->";
								trace += destinationM;
								cout << trace << endl;

							}
						}
					}
				}
			}
		}
	}
}

void ChangeREdge(int **&Array, Router *&List, int rsize) {
	string R1 = "R1", R2 = "R3";
	int edge = 9, ind1, ind2;
	cout << "Enter the name of the first Router : " << endl;
	cin >> R1;
	cout << "Enter the name of the 2nd Router : " << endl;
	cin >> R2;
	cout << "Enter the value of new edge : " << endl;
	cin >> edge;


	for (int i = 0; i < rsize; ++i)
	{
		if (List[i].address == R1)
			ind1 = i;
		if (List[i].address == R2)
			ind2 = i;
	}
	Array[ind1][ind2] = edge;
	Array[ind2][ind1] = edge;

}
void ChangeMEdge(int **&GraphArray, Machine *&ListM, Router *&List, int size, int rsize) {
	string M = "M6";
	int edge = 9;
	cout << "Enter the name of the Machine whose Edge to be changed " << endl;
	cin >> M;
	cout << "Enter the name of the Machine whose Ege to be changed " << endl;
	cin >> edge;
	for (int i = 0; i < (size - rsize); ++i)
	{
		if (ListM[i].address == M)
		{
			for (int j = 0; j < rsize; ++j)
			{
				if (List[j].address == ListM[i].router)
				{
					GraphArray[i][j + (size - rsize)] = edge;
					GraphArray[j + (size - rsize)][i] = edge;
				}
			}
		}

	}
}

int main()
{
	int graphsize = 20;
	//cout << "Enter Graph Size: ";
	//cin >> graphsize;
	string *GraphName = new string[graphsize];
	int **GraphArray = new int*[graphsize];
	for (int i = 0; i < graphsize; i++)
		GraphArray[i] = new int[graphsize];
	int routerSize = 5;
	//cout << "Enter Size of Routers: ";
	//cin >> routerSize;
	int **Array = new int*[routerSize];
	for (int i = 0; i < routerSize; i++)
		Array[i] = new int[routerSize];

	Router *List = new Router[routerSize];
	Machine *ListM = new Machine[graphsize - routerSize];

	Message Text(1, 1, "M3", "M12", "BHAI CHA GAYA HAIII!!!!!!");

	FileRead(GraphName, GraphArray, graphsize); //File Reading
	makeRouterMatrix(Array, GraphArray, graphsize, routerSize); //Making Router Matrix for Dijkstra and stuff
	initialiseRM(GraphName, GraphArray, ListM, List, graphsize, routerSize); //Naming routers and machines and stuff
	routingTable(GraphArray, ListM, List, graphsize, routerSize); //Making routing table and stuff


	int opt;

	cout << "                     ___________________________________" << endl;
	cout << "	             | WELCOME TO  NETWORKING SYSTEM   |" << endl;
	cout << "                     -----------------------------------" << endl << endl;
	while (1)
	{
		cout << "**************************************************************************" << endl << endl
			<< "* Enter 1 to Send Text                                                   *" << endl << "*" << endl
			<< "* Enter 2 to Print Path b/w two machines                                 *" << endl << "*" << endl
			<< "* Enter 3 to Print Path from one machine to every other machine          *" << endl << "*" << endl
			<< "* Enter 4 to Print path from every other machine to a single machine     *" << endl << "*" << endl
			<< "* Enter 5 to change edge b/w two routers                                 *" << endl << "*" << endl
			<< "* Enter 6 to change edge b/w a machine and a router                      *" << endl << "*" << endl
			<< "* Enter 7 to  exit                                                       *" << endl << "*" << endl
			<< "**************************************************************************" << endl;
		cin >> opt;
		if (opt == 1)
		{
			Message M;
			string Text;
			string t;
			int p;
			int i;
			string source;
			string destination;
			cout << "Enter the source machine:";
			cin >> source;
			M.source = source;
			cout << "Enter the destination machine of the message:";
			cin >> destination;
			M.destination = destination;
			cout << "Enter the text:";
			cin >> t;
			M.text = t;
			cout << "Enter the priority:";
			cin >> p;
			M.priority = p;
			cout << "Enter the id of the message:";
			cin >> i;
			M.id = i;
			SendText(M, Array, ListM, List, graphsize, routerSize);
		}
		if (opt == 2)
		{
			printPath1_1(Array, ListM, List, graphsize, routerSize);
		}
		if (opt == 3)
		{
			printPath1_All(Array, ListM, List, graphsize, routerSize);
		}
		if (opt == 4)
		{
			printPathAll_1(Array, ListM, List, graphsize, routerSize);
		}
		if (opt == 5)
		{
			ChangeREdge(Array, List, routerSize);
			makeRouterMatrix(Array, GraphArray, graphsize, routerSize); //Making Router Matrix for Dijkstra and stuff
			initialiseRM(GraphName, GraphArray, ListM, List, graphsize, routerSize); //Naming routers and machines and stuff
			routingTable(GraphArray, ListM, List, graphsize, routerSize); //Making routing table and stuff

		}
		if (opt == 6)
		{
			ChangeMEdge(GraphArray, ListM, List, graphsize, routerSize);
			makeRouterMatrix(Array, GraphArray, graphsize, routerSize); //Making Router Matrix for Dijkstra and stuff
			initialiseRM(GraphName, GraphArray, ListM, List, graphsize, routerSize); //Naming routers and machines and stuff
			routingTable(GraphArray, ListM, List, graphsize, routerSize); //Making routing table and stuff

		}

		if (opt == 7)
		{
			exit(-1);
		}
	}



	system("pause");
	return 0;
}