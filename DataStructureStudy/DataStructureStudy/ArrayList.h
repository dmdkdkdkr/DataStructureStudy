#pragma once
#include <tuple>
#include <algorithm>
#include "LinkedStack.h"

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
		while (i != j)
		{
			for (; i < iRight; i++)
			{
				if (pArr[i] > pArr[iPivot])
					break;
			}

			for (; j > iLeft; j--)
			{
				if (pArr[j] < pArr[iPivot])
					break;
			}

			if (i == j) break;

			T temp = pArr[i];
			pArr[i] = pArr[j];
			pArr[j] = temp;
		}

		if (pArr[i] > pArr[iPivot])
		{
			T temp = pArr[iPivot];
			pArr[iPivot] = pArr[i];
			pArr[i] = temp;
		}

		if (i - iLeft > 1) pStack->Push(std::make_tuple(iLeft, i - 1));
		if (iPivot - i > 1) pStack->Push(std::make_tuple(i + 1, iPivot));
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
bool ArrayList<T>::IsFull() const { return count == maxCount; }

template<typename T>
bool ArrayList<T>::IsEmpty() const { return count == 0; }
