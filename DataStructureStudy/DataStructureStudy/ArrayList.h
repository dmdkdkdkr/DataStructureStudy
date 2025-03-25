#pragma once
#include <tuple>
#include <algorithm>
#include "LinkedStack.h"
#include "LinkedQueue.h"
#include "LinkedList.h"
#include "Heap.h"

template<typename T>
class ArrayList
{
private:
	int count;
	int maxCount;
	T* pArr;

public:
	ArrayList(int _maxCount);
	~ArrayList();

	T operator[](int i);

	bool Add(T _value, int _index);
	bool AddToLast(T _value);
	bool Remove(int _index);
	bool RemoveFromLast();
	bool Clear();
	T Get(int _index) const;
	bool Contains(T _data) const;

	int Count() const;
	void Display() const;

	void SelectionSort();
	void BubbleSort();
	void QuickSort();
	void InsertionSort();
	void ShellSort();
	void MergeSort();
	void HeapSort();

	int BinarySearch(T data, bool onSort = false);

private:
	bool IsFull() const;
	bool IsEmpty() const;
};

template<typename T>
inline ArrayList<T>::ArrayList(int _maxCount) : count(0), maxCount(_maxCount)
{
	if (_maxCount < 1)
		printf("%d: _maxCount값은 최소 1 이상이어야 합니다. 값이 1로 재조정됩니다.", _maxCount);

	maxCount = std::max<int>(maxCount, 1);
	pArr = new T[maxCount];
}

template<typename T>
inline ArrayList<T>::~ArrayList()
{
	delete[] pArr;
}

template<typename T>
inline T ArrayList<T>::operator[](int i)
{
	return Get(i);
}

template<typename T>
bool ArrayList<T>::Add(T _value, int _index)
{
	if (IsFull())
	{
		printf("배열 리스트가 꽉 찼습니다. #ArrayList<T>::Add(T _value, int _index)\n");
		return false;
	}

	if (_index < 0 || _index > count)
	{
		printf("%d => 유효하지 않은 인덱스 값입니다. #ArrayList<T>::Add(T _value, int _index)\n", _index);
		return false;
	}

	for (int i = count - 1; i >= _index; i--)
		pArr[i + 1] = pArr[i];
	pArr[_index] = _value;
	count++;

	return true;
}

template<typename T>
bool ArrayList<T>::AddToLast(T value)
{
	return Add(value, count);
}

template<typename T>
bool ArrayList<T>::Remove(int _index)
{
	if (IsEmpty())
	{
		printf("배열 리스트가 비었습니다. #ArrayList<T>::Remove(int _index)\n");
		return false;
	}

	if (_index < 0 || _index >= count)
	{
		printf("%d => 유효하지 않은 인덱스 값입니다. #ArrayList<T>::Remove(int _index)\n", _index);
		return false;
	}

	for (int i = _index; i < count - 1; i++)
		pArr[i] = pArr[i + 1];
	count--;

	return true;
}

template<typename T>
bool ArrayList<T>::RemoveFromLast()
{
	return Remove(count - 1);
}

template<typename T>
bool ArrayList<T>::Clear()
{
	count = 0;
	return true;
}

template<typename T>
T ArrayList<T>::Get(int _index) const
{
	T data = T();

	if (IsEmpty())
	{
		printf("배열 리스트가 비었습니다. #ArrayList<T>::Get(int _index)\n");
		return data;
	}

	if (_index < 0 || _index >= count)
	{
		printf("%d => 유효하지 않은 인덱스 값입니다. #ArrayList<T>::Get(int _index)\n", _index);
		return data;
	}

	return pArr[_index];
}

template<typename T>
bool ArrayList<T>::Contains(T _data) const
{
	if (IsEmpty()) return false;

	for (int i = 0; i < count; i++)
	{
		if (pArr[i] == _data)
			return true;
	}

	return false;
}

template<typename T>
int ArrayList<T>::Count() const { return count; }

template<typename T>
void ArrayList<T>::Display() const
{
	printf("\nDisplay ArrayList => count: %d\n", count);

	for (int i = 0; i < count; i++)
	{
		printf("\t[%d]: %d\n", i, pArr[i]);
	}

	printf("End displaying arrayList\n");
}

template<typename T>
inline void ArrayList<T>::SelectionSort()
{
	if (count < 2) return;

	for (int i = 0; i < count - 1; i++)
	{
		int iMin = i;

		for (int j = i + 1; j < count; j++)
		{
			if (pArr[j] < pArr[iMin])
				iMin = j;
		}

		if (iMin != i)
		{
			int temp = pArr[iMin];
			pArr[iMin] = pArr[i];
			pArr[i] = temp;
		}
	}
}

template<typename T>
inline void ArrayList<T>::BubbleSort()
{
	if (count < 2) return;

	for (int i = count - 1; i >= 1; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (pArr[j] > pArr[j + 1])
			{
				int temp = pArr[j];
				pArr[j] = pArr[j + 1];
				pArr[j + 1] = temp;
			}
		}
	}
}

template<typename T>
void ArrayList<T>::QuickSort()
{
	if (count < 2) return;

	using Range = std::tuple<int, int>;

	int limit = 0;
	LinkedStack<Range>* pStack = new LinkedStack<Range>();
	pStack->Push(std::make_tuple(0, count - 1));
	while (!pStack->IsEmpty())
	{
		auto range = pStack->Pop();
		int iLeft = std::get<0>(range);
		int iPivot = std::get<1>(range);
		int iRight = iPivot - 1;

		int i = iLeft;
		int j = iRight;
		while (i < j)
		{
			for (; i < j; i++)
			{
				if (pArr[i] > pArr[iPivot])
					break;
			}

			for (; j > i; j--)
			{
				if (pArr[j] < pArr[iPivot])
					break;
			}

			if (i == j) break;

			T temp = pArr[i];
			pArr[i] = pArr[j];
			pArr[j] = temp;

			limit++;
			if (limit > 100) break;
		}

		if (pArr[i] > pArr[iPivot])
		{
			T temp = pArr[iPivot];
			pArr[iPivot] = pArr[i];
			pArr[i] = temp;
		}

		if (i - iLeft > 1) pStack->Push(std::make_tuple(iLeft, i));
		if (iPivot - i > 1) pStack->Push(std::make_tuple(i + 1, iPivot));

		limit++;
		if (limit > 10) break;
	}

	delete pStack;
}

template<typename T>
void ArrayList<T>::InsertionSort()
{
	if (count < 2) return;

	for (int i = 1; i < count; i++)
	{
		int temp = pArr[i];
		int j = i;
		for (; j > 0; j--)
		{
			if (pArr[j - 1] < temp) break;
			pArr[j] = pArr[j - 1];
		}
		pArr[j] = temp;
	}
}

template<typename T>
void ArrayList<T>::ShellSort()
{
	if (count < 2) return;

	int _gap = count / 2;
	while (_gap > 0)
	{
		for (int i = 0; i < _gap; i++)
		{
			for (int j = i + _gap; j < count; j += _gap)
			{
				int temp = pArr[j];
				int k = j;
				for (; k > i; k -= _gap)
				{
					if (pArr[k - _gap] < temp) break;
					pArr[k] = pArr[k - _gap];
				}
				pArr[k] = temp;
			}
		}
		_gap /= 2;
	}
}

template<typename T>
inline void ArrayList<T>::MergeSort()
{
	if (count < 2) return;

	using Range = std::tuple<int, int>;

	// Split
	LinkedQueue<Range>* pSplitQueue = new LinkedQueue<Range>();
	LinkedQueue<Range>* pMergeQueue = new LinkedQueue<Range>();
	pSplitQueue->Enqueue(std::make_tuple(0, count - 1));
	while (!pSplitQueue->IsEmpty())
	{
		auto range = pSplitQueue->Dequeue();
		int iStart = std::get<0>(range);
		int iEnd = std::get<1>(range);
		int count = (iEnd - iStart) + 1;
		if (count > 1)
		{
			int iMid = iStart + (count / 2);
			pSplitQueue->Enqueue(std::make_tuple(iStart, iMid - 1));
			pSplitQueue->Enqueue(std::make_tuple(iMid, iEnd));
		}
		else
		{
			pMergeQueue->Enqueue(range);
		}
	}

	// Merge
	LinkedQueue<Range>* pResultQueue = new LinkedQueue<Range>();
	LinkedList<T>* pLeft = new LinkedList<T>();
	LinkedList<T>* pRight = new LinkedList<T>();
	while (pMergeQueue->Count() > 1)
	{
		while (pMergeQueue->Count() > 1)
		{
			auto left = pMergeQueue->Dequeue();
			auto right = pMergeQueue->Dequeue();

			int iLeftStart = std::get<0>(left);
			int iLeftEnd = std::get<1>(left);
			int iRightStart = std::get<0>(right);
			int iRightEnd = std::get<1>(right);

			pLeft->Clear();
			for (int i = iLeftStart; i <= iLeftEnd; i++)
				pLeft->AddToLast(pArr[i]);

			pRight->Clear();
			for (int i = iRightStart; i <= iRightEnd; i++)
				pRight->AddToLast(pArr[i]);

			int iArr = iLeftStart;
			while (pLeft->Count() > 0 && pRight->Count() > 0)
			{
				int lValue = pLeft->Get(0);
				int rValue = pRight->Get(0);
				if (lValue < rValue)
				{
					pArr[iArr] = lValue;
					pLeft->Remove(0);
				}
				else
				{
					pArr[iArr] = rValue;
					pRight->Remove(0);
				}
				iArr++;
			}

			while (pLeft->Count() > 0)
			{
				pArr[iArr] = pLeft->Get(0);
				pLeft->Remove(0);
				iArr++;
			}

			while (pRight->Count() > 0)
			{
				pArr[iArr] = pRight->Get(0);
				pRight->Remove(0);
				iArr++;
			}

			pResultQueue->Enqueue(std::make_tuple(iLeftStart, iRightEnd));
		}

		while (pMergeQueue->Count() > 0)
			pResultQueue->Enqueue(pMergeQueue->Dequeue());

		while (pResultQueue->Count() > 0)
			pMergeQueue->Enqueue(pResultQueue->Dequeue());
	}

	delete pRight;
	delete pLeft;
	delete pResultQueue;
	delete pMergeQueue;
	delete pSplitQueue;
}

template<typename T>
inline void ArrayList<T>::HeapSort()
{
	Heap<T>* pHeap = new Heap<T>(count, false);

	for (int i = 0; i < count; i++) pHeap->Insert(pArr[i]);
	for (int i = 0; i < count; i++)
	{
		pArr[i] = pHeap->Peek();
		pHeap->Remove(pArr[i]);
	}

	delete pHeap;
}

template<typename T>
inline int ArrayList<T>::BinarySearch(T data, bool doSort)
{
	if (IsEmpty()) return -1;
	if (doSort) QuickSort();

	int iStart = 0;
	int iEnd = count - 1;
	while (iStart <= iEnd)
	{
		int iMid = (iStart + iEnd) / 2;
		if (data == pArr[iMid])
		{
			return iMid;
		}
		else if (data < pArr[iMid])
		{
			iEnd = iMid - 1;
		}
		else
		{
			iStart = iMid + 1;
		}
	}

	return -1;
}

template<typename T>
bool ArrayList<T>::IsFull() const { return count == maxCount; }

template<typename T>
bool ArrayList<T>::IsEmpty() const { return count == 0; }
