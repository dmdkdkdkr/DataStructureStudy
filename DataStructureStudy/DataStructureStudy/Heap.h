#pragma once
#include <stdio.h>
#include <cmath>
#include <limits>
#include <algorithm>
#include "LinkedGraph.h"

template <typename T>
class Heap
{
private:
	T* arr;
	int count;
	bool bIsMaxHeap;

public:
	Heap(int _capacity, bool _bIsMaxHeap);
	~Heap();

	bool Insert(T _data);
	bool Remove(T _data);
	T Peek();
	void Clear();
	void Display();
	int Count();
	bool IsEmpty();
	bool IsFull();

private:
	int Capacity();
};

template<typename T>
Heap<T>::Heap(int _capacity, bool _bIsMaxHeap) : count(0), bIsMaxHeap(_bIsMaxHeap)
{
	arr = new T[_capacity + 1];
}

template<typename T>
Heap<T>::~Heap()
{
	delete[] arr;
}

template<typename T>
bool Heap<T>::Insert(T _data)
{
	if (IsFull())
	{
		printf("Heap is full\n");
		return false;
	}

	int iChild = count + 1;
	int iParent = 0;
	arr[iChild] = _data;

	while (iChild > 1)
	{
		iParent = iChild / 2;

		if (bIsMaxHeap && (arr[iChild] > arr[iParent]) ||
			!bIsMaxHeap && (arr[iChild] < arr[iParent]))
		{
			T _temp = arr[iParent];
			arr[iParent] = arr[iChild];
			arr[iChild] = _temp;
		}

		iChild = iParent;
	}
	count++;

	return true;
}

template<typename T>
bool Heap<T>::Remove(T _data)
{
	if (IsEmpty())
	{
		printf("Heap is empty\n");
		return false;
	}

	if (bIsMaxHeap)
	{
		if (_data > arr[1])
		{
			printf("Can't find the same node\n");
			return false;
		}
	}
	else
	{
		if (_data < arr[1])
		{
			printf("Can't find the same node\n");
			return false;
		}
	}

	T _nodeData = T();
	int iDel = 0;

	// Find the node
	for (int i = 1; i <= count; i++)
	{
		_nodeData = arr[i];
		if (_nodeData == _data)
		{
			iDel = i;
			break;
		}
	}

	if (iDel == 0)
	{
		printf("Can't find the same node\n");
		return false;
	}

	// Remove node
	arr[iDel] = arr[count];
	count--;

	int iChild = 0;
	int iLeft = 0;
	int iRight = 0;
	while (iDel <= count)
	{
		iLeft = iDel * 2;
		iRight = std::min<int>(iLeft + 1, count);
		iChild = iLeft;

		if (iLeft > count) break;

		if (iLeft != iRight)
		{
			if (bIsMaxHeap && (arr[iRight] > arr[iLeft]) ||
				!bIsMaxHeap && (arr[iRight] < arr[iLeft]))
				iChild = iRight;
		}

		if (bIsMaxHeap && (arr[iDel] >= arr[iChild]) ||
			!bIsMaxHeap && (arr[iDel] <= arr[iChild]))
			break;

		T _temp = arr[iDel];
		arr[iDel] = arr[iChild];
		arr[iChild] = _temp;

		iDel = iChild;
	}

	return true;
}

template<typename T>
T Heap<T>::Peek()
{
	if (IsEmpty())
	{
		printf("Heap is empty\n");
		return T();
	}

	return arr[1];
}

template<typename T>
void Heap<T>::Clear()
{
	int _capacity = Capacity();
	delete[] arr;
	arr = new T[_capacity];
	count = 0;
}

template<typename T>
void Heap<T>::Display()
{
	printf("\nDisplay heap => count: %d\n", count);

	int _lv = 0;
	for (int i = 1; i <= count; i++)
	{
		_lv = (int)(std::log2(i) + std::numeric_limits<double>::epsilon());
		for (int j = 0; j < _lv; j++) printf("\t");
		printf("[Lv:%d] => data: %d\n", _lv, arr[i]);
	}

	printf("End displying heap\n");
}

template<>
void Heap<LinkedGraphEdge>::Display();

template<typename T>
inline int Heap<T>::Count() { return count; }

template<typename T>
inline bool Heap<T>::IsEmpty() { return count == 0; }

template<typename T>
inline bool Heap<T>::IsFull() { return count == Capacity(); }

template<typename T>
inline int Heap<T>::Capacity() { return _msize(arr) / sizeof(T); }
