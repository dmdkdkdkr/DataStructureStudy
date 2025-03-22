#pragma once
#include "ListDataType.h"
#include <stdio.h>

template <typename T>
struct LinkedQueueNode
{
	T data;
	LinkedQueueNode* pNext;

	LinkedQueueNode<T>(T _data);
};

template <typename T>
class LinkedQueue
{
private:
	int count;
	LinkedQueueNode<T>* pFront;
	LinkedQueueNode<T>* pRear;

public:
	LinkedQueue();
	~LinkedQueue();

	bool Enqueue(T data);
	T Dequeue();
	T Peek();
	bool Clear();
	void Display();
	int Count();
	bool IsEmpty();
};

template <typename T>
LinkedQueueNode<T>::LinkedQueueNode(T _data) : data(_data), pNext(NULL) {}

template <typename T>
LinkedQueue<T>::LinkedQueue() : count(0), pFront(NULL), pRear(NULL) {}

template <typename T>
LinkedQueue<T>::~LinkedQueue() { Clear(); }

template <typename T>
bool LinkedQueue<T>::Enqueue(T data)
{
	LinkedQueueNode<T>* pNewNode = new LinkedQueueNode<T>(data);

	if (pFront == NULL)
	{
		pFront = pNewNode;
		pRear = pNewNode;
	}
	else
	{
		pRear->pNext = pNewNode;
		pRear = pNewNode;
	}
	count++;

	return true;
}

template <typename T>
T LinkedQueue<T>::Dequeue()
{
	if (IsEmpty())
	{
		printf("Queue is empty\n");
		return T();
	}

	auto pDel = pFront;
	auto data = pDel->data;
	pFront = pDel->pNext;
	delete pDel;

	count--;
	if (IsEmpty()) pRear = NULL;

	return data;
}

template <typename T>
T LinkedQueue<T>::Peek()
{
	if (IsEmpty())
	{
		printf("Queue is empty\n");
		return NULL;
	}

	return pFront->data;
}

template <typename T>
bool LinkedQueue<T>::Clear()
{
	if (IsEmpty()) return false;

	LinkedQueueNode<T>* pDel = pFront;
	LinkedQueueNode<T>* pNext = NULL;
	while (pDel != NULL)
	{
		pNext = pDel->pNext;
		delete pDel;
		pDel = pNext;
	}

	count = 0;
	pFront = pRear = NULL;

	return true;
}

template <typename T>
void LinkedQueue<T>::Display()
{
	printf("\nDisplay queue => count: %d\n", count);

	LinkedQueueNode<T>* pNode = pFront;
	int i = 0;
	while (pNode != NULL)
	{
		printf("\t[%d]: %d\n", i, pNode->data.data);
		i++;
		pNode = pNode->pNext;
	}

	printf("End displaying queue\n");
}

template <typename T>
int LinkedQueue<T>::Count()
{
	return count;
}

template <typename T>
bool LinkedQueue<T>::IsEmpty()
{
	return (count == 0);
}
