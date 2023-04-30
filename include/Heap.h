#pragma once



template<class T>
class Heap
{
private:
	vector<T> heap;
	bool maxheap;
	void bubble_up(int);
	void bubble_down(int);


public:
	//declare public functions
	Heap();
	Heap(bool);  //constructor that takes only BOOL parameter
	Heap(std::vector<T>, bool); //constructor that takes vector and BOOL parameter
	~Heap();  //destructor
			  //other functions we'll need
	int right(int);
	int left(int);
	int parent(int);
	void Insert(T);
	bool Delete(T&);
	void build_heap();
	void set_sort(bool);
	void swap(int, int);
	int size();
	void print_heap();
	void clear_heap();
};

template<class T>
int Heap<T>::parent(int child)
{
	if (child != 0)
	{
		int i = (child - 1) >> 1;
		return i;
	}
	return -1;
}

template<class T>
int Heap<T>::left(int parent)
{
	int i = (parent * 2) + 1; // 2 * parent + 1
	return (i < size()) ? i : -1;
}

template<class T>
int Heap<T>::right(int parent)
{
	int i = (parent * 2) + 2; // 2 * parent + 2
	return (i < size()) ? i : -1;
}

template<class T>
void Heap<T>::bubble_up(int index)
{
	if (!maxheap)
	{
		while ((index > 0) && (parent(index) >= 0) &&
			(heap[parent(index)].priority < heap[index].priority))
		{
			swap(parent(index), index);
			index = parent(index);
		}
	}
	else {
		while ((index > 0) && (parent(index) >= 0) &&
			(heap[parent(index)].priority > heap[index].priority))
		{
			swap(parent(index), index);
			index = parent(index);
		}
	}

}

template<class T>
void Heap<T>::bubble_down(int index)
{
	int leftChildIndex = left(index);
	int rightChildIndex = right(index);
	int minIndex;

	if (rightChildIndex >= size()) {
		if (leftChildIndex >= size())
			return;
		else
			minIndex = leftChildIndex;
	}
	else {
		if (heap[leftChildIndex].priority <= heap[rightChildIndex].priority)
			minIndex = leftChildIndex;
		else
			minIndex = rightChildIndex;
	}
	if (heap[index].priority > heap[minIndex].priority) {
		swap(index, minIndex);
		bubble_down(minIndex);
	}
}

template<class T>
void Heap<T>::build_heap()  //check value of our bool variable and accordingly do sorting
{
	bubble_up(size() - 1);
}

template<class T>
void Heap<T>::set_sort(bool x)  //set our bool variable ('maxheap'), and sort our heap again
{
	maxheap = x;
	build_heap();
}

template<class T>
void Heap<T>::swap(int x, int y)  //swap two elements in vector
{
	T temp = heap[x];
	heap[x] = heap[y];
	heap[y] = temp;
}

//definition of constructor with 0 parameters
template<class T>
Heap<T>::Heap()
{
	maxheap = false;
}

//definition of constructor with 2 parameters
template<class T>
Heap<T>::Heap(vector<T> vec, bool a)
{
	for (unsigned i = 0; i < vec.size(); i++)
		heap.push_back(vec[i]);

	maxheap = a;
	build_heap();
}

template<class T>
Heap<T>::~Heap()
{
	//blah blah
}

//insert item in heap
template<class T>
void Heap<T>::Insert(T elem)
{
	heap.push_back(elem);
	bubble_up(size() - 1);
}

//search for element in parameter, if elements are found delete _heap_[0]
template<class T>
bool Heap<T>::Delete(T& elem)
{
	if (heap.empty())
	{
		return false;
	}

	//push _heap_[0] to the last place in vector so we can pop it
	for (int i = 1; i < size(); i++)
		swap(i - 1, i);

	elem = heap[size() - 1];

	heap.pop_back();
	return true;
}

//return size of our heap vector
template<class T>
int Heap<T>::size()
{
	return heap.size();
}

template<class T>
void Heap<T>::print_heap()
{
	if (size() == 0)
	{
		cout << "Heap is empty!" << endl;
		return;
	}
	cout << "Printing heap!" << endl;
	for (int i = 0; i < size(); i++)
		cout << heap[i].text << " ";

	cout << endl;
}

template<class T>
void Heap<T>::clear_heap()
{
	//cout << "Clearing heap!" << endl;
	heap.clear();
}