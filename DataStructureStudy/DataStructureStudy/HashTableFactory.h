#pragma once
#include "HashTable.h"
#include "HashTable_LinearProbe.h"
#include "HashTable_Chaining.h"

template<typename TKey, typename TData>
class HashTableFactory
{
public:
	static HashTableBase<TKey, TData>* Create(HashTableType _type, int _size);
};

template<typename TKey, typename TData>
HashTableBase<TKey, TData>* HashTableFactory<TKey, TData>::Create(HashTableType _type, int _size)
{
	HashTableBase<TKey, TData>* pTable = nullptr;
	switch (_type)
	{
	case LINEAR:
		pTable = new HashTable_LinearProbe<TKey, TData>(_size);
		break;
	case CHAINING:
		pTable = new HashTable_Chaining<TKey, TData>(_size);
		break;
	}
	return pTable;
}