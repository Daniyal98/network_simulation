#pragma once
#include <iostream>
using namespace std;
#include <string>


void SWAP(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}
class MinHeap
{
	int *harr;
	int totalsize;
	int psize;
public:
	int getpsize() { return psize; }
	MinHeap(int totalsize);

	void DisplayMinHeap(string *, int *);
	void MinHeapify(int);

	int parent(int i) { return (i - 1) / 2; }


	int left(int i) { return (2 * i + 1); }

	int right(int i) { return (2 * i + 2); }


	int extractMin();


	void decreasenum(int i, int new_val);


	int getMin() { return harr[0]; }


	void deletenum(int i);


	void insertnum(int k);
	int Findnum(int n);
};


void MinHeap::DisplayMinHeap(string *arr, int *arr2)

{
	int i = 0;
	for (int i = 0; i < psize; ++i)
		for (int j = 0; j < psize; ++j)
			if (arr2[j] == harr[i]) {
				cout << i << "  " << arr[j] << " " << harr[i] << endl;
				break;
			}
}
MinHeap::MinHeap(int cap)
{
	psize = 0;
	totalsize = cap;
	harr = new int[cap];
}
int MinHeap::Findnum(int n) {
	for (int i = 0; i < psize; ++i)
		if (n == harr[i])
			return i;
}

void MinHeap::insertnum(int k)
{
	if (psize == totalsize)
	{
		cout << "\nOverflow: Could not insertnum\n";
		return;
	}


	psize++;
	int i = psize - 1;
	harr[i] = k;


	while (i != 0 && harr[parent(i)] > harr[i])
	{
		SWAP(&harr[i], &harr[parent(i)]);
		i = parent(i);
	}
}


void MinHeap::decreasenum(int i, int new_val)
{
	harr[i] = new_val;
	while (i != 0 && harr[parent(i)] > harr[i])
	{
		SWAP(&harr[i], &harr[parent(i)]);
		i = parent(i);
	}
}

int MinHeap::extractMin()
{
	if (psize <= 0)
		return INT_MAX;
	if (psize == 1)
	{
		psize--;
		return harr[0];
	}

	int root = harr[0];
	harr[0] = harr[psize - 1];
	psize--;
	MinHeapify(0);

	return root;
}



void MinHeap::deletenum(int i)
{
	decreasenum(i, INT_MIN);
	extractMin();
}


void MinHeap::MinHeapify(int i)
{
	int l = left(i);
	int r = right(i);
	int smallest = i;
	if (l < psize && harr[l] < harr[i])
		smallest = l;
	if (r < psize && harr[r] < harr[smallest])
		smallest = r;
	if (smallest != i)
	{
		SWAP(&harr[i], &harr[smallest]);
		MinHeapify(smallest);
	}
}