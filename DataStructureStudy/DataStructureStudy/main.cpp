#include <stdio.h>
#include "ArrayList.h"

int main()
{
	ArrayList<int>* pList = new ArrayList<int>(10);
	pList->AddToLast(5);
	pList->AddToLast(4);
	pList->AddToLast(2);
	pList->AddToLast(3);
	pList->AddToLast(1);
	pList->Display();

	pList->BubbleSort();
	pList->Display();

	delete pList;
	return 0;
}