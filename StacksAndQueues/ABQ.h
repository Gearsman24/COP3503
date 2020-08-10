#pragma once
#include <stdexcept>

//Declarations
template<typename T>
class ABQ
{
private:
	T* queue;
	unsigned int maxCapacity;
	unsigned int size;
	const float SCALE_FACTOR = 2.0; //Default

public:
	//Constructors
	ABQ(); //Default
	ABQ(int capacity); //With initial capacity
	ABQ(const ABQ& d); //Copy

	//Copy Assignment Operator
	ABQ& operator=(const ABQ& d);

	//Destructor
	~ABQ();

	void enqueue(T data);
	T dequeue();
	T peek();

	//Getters
	unsigned int getSize();
	unsigned int getMaxCapacity();
	T* getData();
};

/*Definitions*/

//Default Constructor
template<typename T>
ABQ<T>::ABQ()
{
	maxCapacity = 1;
	size = 0;
	queue = new T[maxCapacity];

}

//Constructor with specified starting max capacity
template<typename T>
ABQ<T>::ABQ(int capacity)
{
	maxCapacity = capacity;
	size = 0;
	queue = new T[capacity];

}

//Copy Constructor
template<typename T>
ABQ<T>::ABQ(const ABQ& d)
{
	maxCapacity = d.maxCapacity;
	size = d.size;

	//1. Allocate Space
	queue = new T[maxCapacity];

	//2. Copy Each Element
	for (unsigned int i = 0; i < maxCapacity; i++)
	{
		queue[i] = d.queue[i];
	}

}

//Copy Assignmetn Operator
template<typename T>
ABQ<T>& ABQ<T>::operator=(const ABQ& d)
{
	maxCapacity = d.maxCapacity;
	size = d.size;

	//1. Delete old data
	delete[] queue;

	//2. Allocate Space
	queue = new T[maxCapacity];

	//3. Copy Each Element
	for (unsigned int i = 0; i < maxCapacity; i++)
	{
		queue[i] = d.queue[i];
	}

	return *this;
}

//Destructor
template<typename T>
ABQ<T>::~ABQ()
{
	delete[] queue;
}

//Add a new item to the end of the queue, resize if necessary
template<typename T>
void ABQ<T>::enqueue(T data)
{
	if (size == maxCapacity)
	{
		maxCapacity = maxCapacity * SCALE_FACTOR;
	}
	size = size + 1;
	unsigned int smallest;

	//1. Create a new array based on the desired size
	T* nextQueue = new T[maxCapacity];
	nextQueue[0] = data;

	//2. Copy elements from the old array to the new array
	if (size < maxCapacity)
	{
		smallest = size;
	}
	else
	{
		smallest = maxCapacity;
	}

	//3. QUEUE: Add to back of line
	for (unsigned int i = 1; i < smallest; i++)
	{
		nextQueue[i] = queue[i - 1];
	}

	//4. Delete the old array
	delete[] queue;

	//5. Redirect the pointer
	queue = nextQueue;
}

//Remove the item at the front of the queue, resize if necessary, return the value removed
template<typename T>
T ABQ<T>::dequeue()
{
	//Exception runtime_error if stack is empty
	if (size == 0)
	{
		throw std::runtime_error("An error has occurred");
	}

	T response = peek();
	size = size - 1;

	if (((float)size / (float)maxCapacity) < (1 / SCALE_FACTOR))
	{
		maxCapacity = maxCapacity / SCALE_FACTOR;
	}

	//1. Create a new array based on the desired size
	T* nextQueue = new T[maxCapacity];

	//2. Copy elements from the old array to the new array
	unsigned int smallest;
	if (size < maxCapacity)
	{
		smallest = size;
	}
	else
	{
		smallest = maxCapacity;
	}
	for (unsigned int i = 0; i < smallest; i++)
	{
		//The front item is removed
		if (i != maxCapacity)
		{
			nextQueue[i] = queue[i];
		}
	}

	//3. Delete the old array
	delete[] queue;

	//4. Redirect the pointer
	queue = nextQueue;

	return response;


}



//Return the value of the item at the front of the queue, without removing it
template<typename T>
T ABQ<T>::peek()
{
	//Throws a runtime_error if the queue is empty
	if (size == 0)
	{
		throw std::runtime_error("An error has occurred");
	}

	return queue[size - 1];
}

//Returns the current number of items in the ABQ
template<typename T>
unsigned int ABQ<T>::getSize()
{
	return size;
}

//Returns the current max capacity of the ABQ
template<typename T>
unsigned int ABQ<T>::getMaxCapacity()
{
	return maxCapacity;
}

//Returns the array representing the queue
template<typename T>
T* ABQ<T>::getData()
{
	return queue;
}