#include <stdio.h>
#include "ArrayList.h"

int main()
{
	ArrayList<int>* pList = new ArrayList<int>(10);
	pList->AddToLast(8);
	pList->AddToLast(5);
	pList->AddToLast(7);
	pList->AddToLast(1);
	pList->AddToLast(6);
	pList->AddToLast(2);
	pList->Display();

	pList->QuickSort();
	pList->Display();

	delete pList;

	return 0;
}