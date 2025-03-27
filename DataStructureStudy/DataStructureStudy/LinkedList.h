#pragma once
#include <stdio.h>

template <typename T>
class LinkedListNode
{
public:
	T data;
	LinkedListNode<T>* pPrev;
	LinkedListNode<T>* pNext;

	LinkedListNode(T _data);
};

template <typename T>
class LinkedList
{
private:
	int count;
	LinkedListNode<T>* pHead;

public:
	LinkedList();
	~LinkedList();

	bool Add(T _data, int _index);
	bool Add(LinkedList<T>* pList);
	bool AddToLast(T _data);
	bool Remove(int _index);
	bool Remove(T data);
	bool RemoveFromLast();
	bool Clear();
	T Get(int _index) const;
	T Find(T _data);
	bool IsEmpty() const;
	int Count() const;
	bool Reverse();
	void Display() const;

	T operator[](int i) const;
};


template <typename T>
LinkedListNode<T>::LinkedListNode(T _data) : data(_data), pPrev(NULL), pNext(NULL) {}

template <typename T>
LinkedList<T>::LinkedList() : count(0), pHead(NULL) {}

template <typename T>
LinkedList<T>::~LinkedList()
{
	Clear();
}

template <typename T>
bool LinkedList<T>::Add(T _data, int _index)
{
	if (_index < 0 || _index > count)
	{
		printf("Invalid index: [%d]\n", _index);
		return false;
	}

	LinkedListNode<T>* pNew = new LinkedListNode<T>(_data);
	if (pHead == NULL)
	{
		pHead = pNew;
		pHead->pPrev = pHead;
		pHead->pNext = pHead;
	}
	else
	{
		LinkedListNode<T>* pPrev = NULL;
		LinkedListNode<T>* pNext = NULL;

		if (_index == 0)
		{
			pPrev = pHead->pPrev;
			pNext = pHead;

			pHead = pNew;
		}
		else
		{
			pNext = pHead;
			for (int i = 0; i < _index; i++)
			{
				pPrev = pNext;
				pNext = pNext->pNext;
			}
		}

		pPrev->pNext = pNew;
		pNew->pPrev = pPrev;
		pNew->pNext = pNext;
		pNext->pPrev = pNew;
	}
	count++;

	return true;
}

template <typename T>
bool LinkedList<T>::Add(LinkedList<T>* pList)
{
	if (pList == NULL) return false;
	if (pList->IsEmpty()) return false;

	LinkedListNode<T>* pPrevLast = pHead;
	LinkedListNode<T>* pNextFirst = pList->pHead;
	LinkedListNode<T>* pNextLast = pNextFirst;

	while (pPrevLast->pNext != pHead) pPrevLast = pPrevLast->pNext;
	while (pNextLast->pNext != pNextFirst) pNextLast = pNextLast->pNext;

	pPrevLast->pNext = pNextFirst;
	pNextFirst->pPrev = pPrevLast;
	pNextLast->pNext = pHead;
	pHead->pPrev = pNextLast;

	count += pList->Count();
	pList->pHead = NULL;
	pList->count = 0;

	return false;
}

template <typename T>
bool LinkedList<T>::AddToLast(T _data)
{
	return Add(_data, count);
}

template <typename T>
bool LinkedList<T>::Remove(int _index)
{
	if (IsEmpty())
	{
		printf("List is empty\n");
		return false;
	}

	if (_index < 0 || _index >= count)
	{
		printf("Invalid index: [%d]\n", _index);
		return false;
	}

	LinkedListNode<T>* pDel = NULL;
	LinkedListNode<T>* pPrev = NULL;
	LinkedListNode<T>* pNext = NULL;

	if (_index == 0)
	{
		pDel = pHead;
		pHead = pDel->pNext;
	}
	else
	{
		pDel = pHead;
		for (int i = 0; i < _index; i++) pDel = pDel->pNext;
	}

	pPrev = pDel->pPrev;
	pNext = pDel->pNext;
	pPrev->pNext = pNext;
	pNext->pPrev = pPrev;
	delete pDel;

	count--;
	if (count == 0) pHead = NULL;

	return false;
}

template<typename T>
bool LinkedList<T>::Remove(T data)
{
	if (IsEmpty())
	{
		printf("LinkedList is empty\n");
		return false;
	}

	LinkedListNode<T>* pNode = pHead;
	LinkedListNode<T>* pPrev = NULL;
	LinkedListNode<T>* pNext = NULL;
	while (pNode != NULL)
	{
		pPrev = pNode->pPrev;
		pNext = pNode->pNext;
		if (data == pNode->data)
		{
			pPrev->pNext = pNext;
			pNext->pPrev = pPrev;
			break;
		}
		pNode = pNode->pNext;
	}

	if (pNode == NULL)
	{
		printf("Can't find the node that have same data\n");
		return false;
	}

	delete pNode;
	count--;
	if (IsEmpty()) pHead = NULL;

	return true;
}

template <typename T>
bool LinkedList<T>::RemoveFromLast()
{
	return Remove(count - 1);
}

template <typename T>
bool LinkedList<T>::Clear()
{
	if (IsEmpty()) return true;
	while (count > 0) Remove(0);
	return true;
}

template <typename T>
T LinkedList<T>::Get(int _index) const
{
	if (IsEmpty())
	{
		printf("List is empty\n");
		return T();
	}

	if (_index < 0 || _index >= count)
	{
		printf("Invalid index: [%d]\n", _index);
		return T();
	}

	LinkedListNode<T>* pCur = pHead;
	if (_index < count / 2)
	{
		for (int i = 0; i < _index; i++)
			pCur = pCur->pNext;
	}
	else
	{
		for (int i = 0; i < count - _index; i++)
			pCur = pCur->pPrev;
	}

	return pCur->data;
}

template<typename T>
T LinkedList<T>::Find(T _data)
{
	T ret = T();

	if (IsEmpty()) return ret;

	LinkedListNode<T>* pNode = pHead;
	do
	{
		if (pNode->data == _data)
		{
			ret = pNode->data;
			break;
		}
		pNode = pNode->pNext;
	} while (pNode != pHead);

	return ret;
}

template <typename T>
inline int LinkedList<T>::Count() const { return count; }

template <typename T>
bool LinkedList<T>::Reverse()
{
	if (IsEmpty()) return true;

	LinkedListNode<T>* pCur = pHead;
	LinkedListNode<T>* pTemp = NULL;

	for (int i = 0; i < count; i++)
	{
		pTemp = pCur->pNext;
		pCur->pNext = pCur->pPrev;
		pCur->pPrev = pTemp;
		pCur = pTemp;
	}
	pHead = pCur->pNext;

	return true;
}

template <typename T>
void LinkedList<T>::Display() const
{
	LinkedListNode<T>* pCur = pHead;

	printf("\nDisplay LinkedList => count: %d\n", count);
	for (int i = 0; i < count; i++)
	{
		printf("\tNode[%d]: %d\n", i, pCur->data);
		pCur = pCur->pNext;
	}
	printf("End LinkedList\n");
}

template<typename T>
inline T LinkedList<T>::operator[](int i) const { return Get(i); }

template <typename T>
inline bool LinkedList<T>::IsEmpty() const { return count == 0; }