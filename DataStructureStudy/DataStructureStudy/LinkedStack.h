#pragma once
#include <stdio.h>

template <typename T>
class LinkedStack
{
	class LinkedStackNode
	{
	public:
		T data;
		LinkedStackNode* pNext;

		LinkedStackNode(T data);
	};

private:
	int count;
	LinkedStackNode* pTop = NULL;

public:
	LinkedStack();
	~LinkedStack();

	bool Push(T data);
	T Pop();
	T Peek();
	bool Clear();
	void Display();
	int Count();
	bool IsEmpty();
};

template<typename T>
LinkedStack<T>::LinkedStackNode::LinkedStackNode(T data) : data(data), pNext(NULL) {}

template<typename T>
LinkedStack<T>::LinkedStack() : count(0), pTop(NULL) {}

template<typename T>
LinkedStack<T>::~LinkedStack() { Clear(); }

template<typename T>
bool LinkedStack<T>::Push(T data)
{
	LinkedStackNode* pNewNode = new LinkedStackNode(data);
	pNewNode->pNext = pTop;
	pTop = pNewNode;
	count++;

	return true;
}

template<typename T>
T LinkedStack<T>::Pop()
{
	T data = T();

	if (IsEmpty())
	{
		printf("Stack is empty\n");
		return data;
	}

	LinkedStackNode* pPopped = pTop;
	data = pPopped->data;
	pTop = pTop->pNext;
	delete pPopped;
	count--;

	return data;
}

template<typename T>
T LinkedStack<T>::Peek()
{
	T data = T();

	if (IsEmpty())
	{
		printf("Stack is empty\n");
		return data;
	}

	data = pTop->data;

	return data;
}

template<typename T>
bool LinkedStack<T>::Clear()
{
	if (IsEmpty()) return false;

	LinkedStackNode* pDel = pTop;
	LinkedStackNode* pNext = NULL;
	while (pDel != NULL)
	{
		pNext = pDel->pNext;
		delete pDel;
		pDel = pNext;
	}

	count = 0;
	pTop = NULL;

	return true;
}

template<typename T>
void LinkedStack<T>::Display()
{
	printf("\nDisplay LinkedStack => count: %d\n", count);

	LinkedStackNode* pNode = pTop;
	int h = count;
	while (pNode != NULL)
	{
		printf("\t[%d]: %d\n", h, pNode->data);
		h--;
		pNode = pNode->pNext;
	}

	printf("End displaying LinkedStack\n");
}

template<typename T>
inline int LinkedStack<T>::Count()
{
	return count;
}

template<typename T>
inline bool LinkedStack<T>::IsEmpty()
{
	return count == 0;
}
