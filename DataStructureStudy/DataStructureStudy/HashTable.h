#pragma once
#include <cmath>
#include <algorithm>

template<typename TKey, typename TData>
class HashTableData
{
public:
	TKey key;
	TData data;
	bool isEmpty;

	HashTableData() : isEmpty(true) {}
};

template<typename TKey, typename TData>
class HashTable
{
	int count;
	int size;
	HashTableData<TKey, TData>* pTable;

public:
	HashTable(int _size);
	~HashTable();

	bool Add(TKey key, TData data);
	bool Remove(TKey key);
	void Clear();
	TData Get(TKey key) const;
	void Display() const;

	int Count() const;
	bool IsEmpty() const;
	bool IsFull() const;

	TData operator[](TKey key) const;

private:
	int HashFunc(TKey key) const;
	int GetOffset(TKey key) const;
	bool IsBucketFull(int i) const;
	int GetNearestPrime(int n) const;
};

template<typename TKey, typename TData>
HashTable<TKey, TData>::HashTable(int _size) : count(0), size(_size)
{
	size = GetNearestPrime(size);
	pTable = new HashTableData<TKey, TData>[size]();
}

template<typename TKey, typename TData>
HashTable<TKey, TData>::~HashTable()
{
	delete[] pTable;
}

template<typename TKey, typename TData>
bool HashTable<TKey, TData>::Add(TKey key, TData data)
{
	if (IsFull())
	{
		printf("해시 테이블이 꽉 찼습니다.\n");
		return false;
	}

	int iAdd = HashFunc(key);
	while (IsBucketFull(iAdd))
	{
		if (pTable[iAdd].key == key)
		{
			printf("%d => 이미 같은 키값을 가지는 데이터가 존재합니다.\n", key);
			return false;
		}

		iAdd = (iAdd + GetOffset(key)) % size;
	}

	pTable[iAdd].key = key;
	pTable[iAdd].data = data;
	pTable[iAdd].isEmpty = false;
	count++;

	return true;
}

template<typename TKey, typename TData>
bool HashTable<TKey, TData>::Remove(TKey key)
{
	if (IsEmpty())
	{
		printf("해시 테이블이 비었습니다.\n");
		return false;
	}

	int iStart = HashFunc(key);
	int i = iStart;
	while (IsBucketFull(i))
	{
		HashTableData<TKey, TData> data = pTable[i];
		if (data.key == key)
		{
			pTable[i].isEmpty = true;
			count--;
			return true;
		}

		i = (i + GetOffset(key)) % size;
		if (i == iStart) break;
	}

	printf("%d => 해당하는 키값을 가진 데이터가 존재하지 않습니다.\n", key);
	return false;
}

template<typename TKey, typename TData>
void HashTable<TKey, TData>::Clear()
{
	if (IsEmpty()) return;

	count = 0;
	delete[] pTable;
	pTable = new HashTableData<TKey, TData>[size]();
}

template<typename TKey, typename TData>
TData HashTable<TKey, TData>::Get(TKey key) const
{
	if (IsEmpty())
	{
		printf("해시 테이블이 비었습니다.\n");
		return HashTableData<TKey, TData>();
	}

	int iStart = HashFunc(key);
	int i = iStart;
	while (IsBucketFull(i))
	{
		HashTableData<TKey, TData> data = pTable[i];
		if (data.key == key) return pTable[i].data;

		i = (i + GetOffset(key)) % size;
		if (i == iStart) break;
	}

	printf("%d => 해당하는 키값을 가진 데이터가 존재하지 않습니다.\n", key);
	return HashTableData<TKey, TData>();;
}

template<typename TKey, typename TData>
void HashTable<TKey, TData>::Display() const
{
	printf("\nDisplay hash table => count: %d, size: %d\n", count, size);
	for (int i = 0; i < size; i++)
	{
		if (IsBucketFull(i))
			printf("\t[%d] => key: %d, data: %d\n", i, pTable[i].key, pTable[i].data);
	}
	printf("End displaying hash table\n");
}

template<typename TKey, typename TData>
inline int HashTable<TKey, TData>::Count() const { return count; }

template<typename TKey, typename TData>
inline bool HashTable<TKey, TData>::IsEmpty() const { return count == 0; }

template<typename TKey, typename TData>
inline bool HashTable<TKey, TData>::IsFull() const { return count == size; }

template<typename TKey, typename TData>
TData HashTable<TKey, TData>::operator[](TKey key) const { return Get(key); }

template<typename TKey, typename TData>
inline int HashTable<TKey, TData>::HashFunc(TKey key) const
{
	int i = (int)key % size;
	return i;
}

template<typename TKey, typename TData>
inline int HashTable<TKey, TData>::GetOffset(TKey key) const { return std::max(1, (size - 1) - HashFunc(key)); }

template<typename TKey, typename TData>
inline bool HashTable<TKey, TData>::IsBucketFull(int i) const { return !pTable[i].isEmpty; }

template<typename TKey, typename TData>
inline int HashTable<TKey, TData>::GetNearestPrime(int n) const
{
	int prime = std::max(2, n);

	for(int i = prime; i < std::numeric_limits<int>::max(); i++)
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
