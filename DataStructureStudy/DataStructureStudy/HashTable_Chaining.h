#pragma once
#include <cmath>
#include "HashTable.h"
#include "LinkedList.h"

template<typename TKey, typename TData>
class HashTable_Chaining : public HashTableBase<TKey, TData>
{
	using HashTableBase<TKey, TData>::count;
	using HashTableBase<TKey, TData>::size;
	using HashTableBase<TKey, TData>::IsFull;
	using HashTableBase<TKey, TData>::IsEmpty;

private:
	LinkedList<HashTableData<TKey, TData>>** ppTable;

public:
	HashTable_Chaining<TKey, TData>(int _size);
	~HashTable_Chaining<TKey, TData>();

	bool Add(TKey key, TData data) override;
	bool Remove(TKey key) override;
	void Clear() override;
	TData Get(TKey key) const override;
	void Display() const override;

	TData operator[](TKey key) const override;

protected:
	int HashFunc(TKey key) const override;
	bool IsAlreadyAdded(int i, TKey key) const;
};

template<typename TKey, typename TData>
HashTable_Chaining<TKey, TData>::HashTable_Chaining(int _size) : HashTableBase<TKey, TData>(_size)
{
	ppTable = new LinkedList<HashTableData<TKey, TData>>*[size]();
	for (int i = 0; i < size; i++)
		ppTable[i] = new LinkedList<HashTableData<TKey, TData>>();
}

template<typename TKey, typename TData>
HashTable_Chaining<TKey, TData>::~HashTable_Chaining()
{
	printf("~HashTable_Chaining() is called\n");
	for (int i = 0; i < size; i++)
		delete ppTable[i];
	delete[] ppTable;
}


template<typename TKey, typename TData>
bool HashTable_Chaining<TKey, TData>::Add(TKey key, TData data)
{
	if (IsFull())
	{
		printf("해시 테이블이 꽉 찼습니다.\n");
		return false;
	}

	int iBucket = HashFunc(key);
	if (IsAlreadyAdded(iBucket, key))
	{
		printf("%d => 이미 같은 키값을 가지는 데이터가 존재합니다.\n", key);
		return false;
	}

	HashTableData<TKey, TData> newData = HashTableData<TKey, TData>();
	newData.key = key;
	newData.data = data;
	ppTable[iBucket]->AddToLast(newData);
	count++;

	return true;
}

template<typename TKey, typename TData>
bool HashTable_Chaining<TKey, TData>::Remove(TKey key)
{
	if (IsEmpty())
	{
		printf("해시 테이블이 비었습니다.\n");
		return false;
	}

	int iBucket = HashFunc(key);
	if (IsAlreadyAdded(iBucket, key))
	{
		auto removeData = HashTableData<TKey, TData>();
		removeData.key = key;
		ppTable[iBucket]->Remove(removeData);
		count--;
		return true;
	}

	printf("%d => 해당하는 키값을 가진 데이터가 존재하지 않습니다.\n", key);
	return false;
}

template<typename TKey, typename TData>
inline void HashTable_Chaining<TKey, TData>::Clear()
{
	count = 0;
	for (int i = 0; i < size; i++)
		ppTable[i]->Clear();
}

template<typename TKey, typename TData>
inline TData HashTable_Chaining<TKey, TData>::Get(TKey key) const
{
	if (IsEmpty())
	{
		printf("해시 테이블이 비었습니다.\n");
		return TData();
	}

	int iBucket = HashFunc(key);
	LinkedList<HashTableData<TKey, TData>>* pList = ppTable[iBucket];
	auto data = HashTableData<TKey, TData>();
	data.key = key;
	auto getted = pList->Find(data);
	if (key != getted.key)
	{
		printf("%d => 해당하는 키값을 가진 데이터가 존재하지 않습니다.\n", key);
		return TData();
	}

	return getted.data;
}

template<typename TKey, typename TData>
inline void HashTable_Chaining<TKey, TData>::Display() const
{
	printf("\nDisplaing hash table => count: %d, size: %d\n", count, size);
	for (int i = 0; i < size; i++)
	{
		LinkedList<HashTableData<TKey, TData>>* pList = ppTable[i];
		if (pList->IsEmpty()) continue;
		for (int j = 0; j < pList->Count(); j++)
		{
			auto data = pList->Get(j);
			printf("\t[%d] => key: %d, data: %d\n", i, data.key, data.data);
		}
	}
	printf("End displaying hash table\n");
}

template<typename TKey, typename TData>
inline TData HashTable_Chaining<TKey, TData>::operator[](TKey key) const { return Get(key); }

template<typename TKey, typename TData>
inline int HashTable_Chaining<TKey, TData>::HashFunc(TKey key) const { return (int)key % size; }

template<typename TKey, typename TData>
bool HashTable_Chaining<TKey, TData>::IsAlreadyAdded(int i, TKey key) const
{
	LinkedList<HashTableData<TKey, TData>>* pList = ppTable[i];
	if (pList->IsEmpty()) return false;

	auto tempData = HashTableData<TKey, TData>();
	tempData.key = key;
	auto addedData = pList->Find(tempData);
	return key == addedData.key;
}