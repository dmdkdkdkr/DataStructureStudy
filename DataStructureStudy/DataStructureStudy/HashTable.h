#pragma once
#include <cmath>
#include <algorithm>

enum HashTableType
{
	LINEAR,
	CHAINING
};

template<typename TKey, typename TData>
class HashTableData
{
public:
	TKey key;
	TData data;
	bool isEmpty;

	HashTableData() : isEmpty(true) {}

	bool operator==(HashTableData<TKey, TData> other);
	bool operator!=(HashTableData<TKey, TData> other);
};

template<typename TKey, typename TData>
inline bool HashTableData<TKey, TData>::operator==(HashTableData<TKey, TData> other) { return key == other.key; }

template<typename TKey, typename TData>
inline bool HashTableData<TKey, TData>::operator!=(HashTableData<TKey, TData> other) { return key != other.key; }

template<typename TKey, typename TData>
class HashTableBase
{
protected:
	int count;
	int size;

public:
	HashTableBase(int _size);
	virtual ~HashTableBase() {}

	virtual bool Add(TKey key, TData data) = 0;
	virtual bool Remove(TKey key) = 0;
	virtual void Clear() = 0;
	virtual TData Get(TKey key) const = 0;
	virtual void Display() const = 0;

	int Count() const;
	bool IsEmpty() const;
	bool IsFull() const;

	virtual TData operator[](TKey key) const = 0;

protected:
	virtual int HashFunc(TKey key) const = 0;

	int GetNearestPrime(int n) const;
};

template<typename TKey, typename TData>
HashTableBase<TKey, TData>::HashTableBase(int _size) : count(0), size(_size)
{
	size = GetNearestPrime(size);
}

template<typename TKey, typename TData>
inline int HashTableBase<TKey, TData>::Count() const { return count; }

template<typename TKey, typename TData>
inline bool HashTableBase<TKey, TData>::IsEmpty() const { return count == 0; }

template<typename TKey, typename TData>
inline bool HashTableBase<TKey, TData>::IsFull() const { return count == size; }

template<typename TKey, typename TData>
int HashTableBase<TKey, TData>::GetNearestPrime(int n) const
{
	int prime = std::max(2, n);

	for (int i = prime; i < std::numeric_limits<int>::max(); i++)
	{
		if (i > 2 && i % 2 == 0) continue;
		if (i > 3 && i % 3 == 0) continue;
		if (i > 5 && i % 5 == 0) continue;

		int root = (int)std::sqrt(i);
		bool isPrime = true;
		for (int j = 7; j <= root; j++)
		{
			if (i % j == 0)
			{
				isPrime = false;
				break;
			}
		}
		if (!isPrime) continue;

		prime = i;
		break;
	}

	return prime;
}
