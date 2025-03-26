#include <stdio.h>
#include "HashTable.h"

int main()
{
	HashTable<int, int>* pHashTable = new HashTable<int, int>(5);
	pHashTable->Add(4, 400);
	pHashTable->Add(4, 400);
	pHashTable->Add(9, 300);
	pHashTable->Add(6, 600);
	pHashTable->Add(7, 700);
	pHashTable->Add(2, 200);
	pHashTable->Display();

	pHashTable->Remove(2);
	pHashTable->Remove(1);
	pHashTable->Display();

	pHashTable->Clear();
	pHashTable->Display();

	pHashTable->Add(60, 1);
	pHashTable->Add(70, 2);
	pHashTable->Display();

	delete pHashTable;
	return 0;
}