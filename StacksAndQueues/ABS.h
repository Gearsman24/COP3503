#pragma once
#include <stdexcept>

//Declarations
template <typename T>
class ABS
{
private:
	T* stack;
	unsigned int maxCapacity;
	unsigned int size;
	const float SCALE_FACTOR = 2.0; //Default

public:
	//Constructors
	ABS(); //Default
	ABS(int capacity); //With initial capacity
	ABS(const ABS& d); //Copy

	//Copy Assignment Operator
	ABS& operator=(const ABS& d);

	//Destructor
	~ABS();

	void push(T data);
	T pop();
	T peek();

	//Getters
	unsigned int getSize();
	unsigned int getMaxCapacity();
	T* getData();
};

/*Definitions*/

//Default Constructor
template<typename T>
ABS<T>::ABS()
{
	maxCapacity = 1;
	size = 0;
	stack = new T[maxCapacity];
}

//Constructor with specified starting max capacity
template<typename T>
ABS<T>::ABS(int capacity)
{
	maxCapacity = capacity;
	size = 0;
	stack = new T[capacity];
}

//Copy Constructor
template<typename T>
ABS<T>::ABS(const ABS& d)
{
	maxCapacity = d.maxCapacity;
	size = d.size;

	//1. Allocate Space
	stack = new T[maxCapacity];

	//2. Copy Each Element
	for (unsigned int i = 0; i < maxCapacity; i++)
	{
		stack[i] = d.stack[i];
	}
}

//Copy Assignment Operator
template<typename T>
ABS<T>& ABS<T>::operator=(const ABS& d)
{
	maxCapacity = d.maxCapacity;
	size = d.size;

	//1. Delete old data
	delete[] stack;

	//2. Allocate Space
	stack = new T[maxCapacity];

	//3. Copy Each Element
	for (unsigned int i = 0; i < maxCapacity; i++)
	{
		stack[i] = d.stack[i];
	}

	return *this;
}

//Destructor
template<typename T>
ABS<T>::~ABS()
{
	delete[] stack;
}

//Add a new item to the top of the stack and resize if necessary
template<typename T>
void ABS<T>::push(T data)
{
	if (size == maxCapacity)
	{
		maxCapacity = maxCapacity * SCALE_FACTOR;
		unsigned int smallest;

		//1. Create a new array based on the desired size
		T* nextStack = new T[maxCapacity];

		//2. Copy elements from the old array to the new array
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
			nextStack[i] = stack[i];
		}

		//3. Delete the old array
		delete[] stack;

		//4. Redirect the pointer
		stack = nextStack;

	}

	//5. STACK: Add to top
	stack[size] = data;
	size++;
}

//Remove the item at the top of the stack, resize if necessary, return the value removed
template<typename T>
T ABS<T>::pop()
{
	T response = peek();
	//Exception runtime_error if stack is empty
	if (size == 0)
	{
		throw std::runtime_error("An error has occurred");
	}

	size = size - 1;

	if (((float)size / (float)maxCapacity) < (1 / SCALE_FACTOR))
	{
		maxCapacity = maxCapacity / SCALE_FACTOR;
	}


	//1. Create a new array based on the desired size
	T* nextStack = new T[maxCapacity];

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
		//The top item is removed
		if (i != maxCapacity)
		{
			nextStack[i] = stack[i];
		}
	}

	//3. Delete the old array
	delete[] stack;

	//4. Redirect the pointer
	stack = nextStack;

	return response;
}

//Return the value of the item at the top of the stack without removing it
template<typename T>
T ABS<T>::peek()
{
	//Exception runtime_error if stack is empty
	if (size == 0)
	{
		throw std::runtime_error("An error has occurred");
	}

	return stack[size - 1];

}

//Returns the current number of items in the ABS
template<typename T>
unsigned int ABS<T>::getSize()
{
	return size;
}

//Returns the current max capacity of the ABS
template<typename T>
unsigned int ABS<T>::getMaxCapacity()
{
	return maxCapacity;
}

//Returns the array representing the stack
template<typename T>
T* ABS<T>::getData()
{
	return stack;
}