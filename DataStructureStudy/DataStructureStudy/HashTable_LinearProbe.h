#pragma once
#include "HashTable.h"

template<typename TKey, typename TData>
class HashTable_LinearProbe : public HashTableBase<TKey, TData>
{
	using HashTableBase<TKey, TData>::count;
	using HashTableBase<TKey, TData>::size;
	using HashTableBase<TKey, TData>::IsFull;
	using HashTableBase<TKey, TData>::IsEmpty;

private:
	HashTableData<TKey, TData>* pTable;

public:
	HashTable_LinearProbe(int _size);
	~HashTable_LinearProbe();

	bool Add(TKey key, TData data) override;
	bool Remove(TKey key) override;
	void Clear() override;
	TData Get(TKey key) const override;
	void Display() const override;

	TData operator[](TKey key) const override;

protected:
	int HashFunc(TKey key) const override;
	int GetOffset(TKey key) const;
	bool IsBucketFull(int i) const;
};

template<typename TKey, typename TData>
HashTable_LinearProbe<TKey, TData>::HashTable_LinearProbe(int _size) : HashTableBase<TKey, TData>(_size)
{
	pTable = new HashTableData<TKey, TData>[size]();
}

template<typename TKey, typename TData>
HashTable_LinearProbe<TKey, TData>::~HashTable_LinearProbe()
{
	delete[] pTable;
}

template<typename TKey, typename TData>
bool HashTable_LinearProbe<TKey, TData>::Add(TKey key, TData data)
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
bool HashTable_LinearProbe<TKey, TData>::Remove(TKey key)
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
void HashTable_LinearProbe<TKey, TData>::Clear()
{
	if (IsEmpty()) return;

	count = 0;
	delete[] pTable;
	pTable = new HashTableData<TKey, TData>[size]();
}

template<typename TKey, typename TData>
TData HashTable_LinearProbe<TKey, TData>::Get(TKey key) const
{
	if (IsEmpty())
	{
		printf("해시 테이블이 비었습니다.\n");
		return TData();
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
	return TData();
}

template<typename TKey, typename TData>
void HashTable_LinearProbe<TKey, TData>::Display() const
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
TData HashTable_LinearProbe<TKey, TData>::operator[](TKey key) const { return Get(key); }

template<typename TKey, typename TData>
inline int HashTable_LinearProbe<TKey, TData>::HashFunc(TKey key) const
{
	int i = (int)key % size;
	return i;
}

template<typename TKey, typename TData>
inline int HashTable_LinearProbe<TKey, TData>::GetOffset(TKey key) const { return std::max(1, (size - 1) - HashFunc(key)); }

template<typename TKey, typename TData>
inline bool HashTable_LinearProbe<TKey, TData>::IsBucketFull(int i) const { return !pTable[i].isEmpty; }