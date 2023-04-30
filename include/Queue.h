#pragma once



template< class T >
class Queue
{
public:
	Queue();//default constructor
	~Queue()//destructor
	{
		delete[] values;
	}
	void enQueue(T);
	T deQueue();
	bool isEmpty();
	bool isFull();
	void Display();
private:
	int size;
	T *values;
	int front;
	int back;
};

template< class T >
Queue<T>::Queue() : size(0), values(new T[size]), front(0), back(0)
{
	/*empty*/
}

template< class T >
bool Queue<T>::isFull()
{
	if ((back + 1) % size == front)
		return 1;
	else
		return 0;
}

template< class T >
void Queue<T>::enQueue(T x)
{
	T *temp = new T[size];
	for (int i = 0; i < size; i++)
		temp[i] = values[i];

	values = NULL;
	values = new T[size + 1];
	for (int i = 0; i < size; i++)
		values[i] = temp[i];

	values[size] = x;
	temp = NULL;
	size++;
}

template< class T >
bool Queue<T>::isEmpty()
{
	if (size == 0)
		return 1;

	else
		return 0;
}

template< class T >
T Queue<T>::deQueue()
{
	T val;
	if (!Queue<T>::isEmpty())
	{
		val = values[front];
		//		values[front] = NULL;
		for (int i = 0; i < size - 1; i++)
			values[i] = values[i + 1];

		size--;
	}
	else
	{
		cout << "Queue is Empty : ";
	}
	return val;
}

template <typename T>
void Queue<T>::Display()
{
	for (int i = 0; i < size; i++)
	{
		cout << values[i] << endl;
	}
}