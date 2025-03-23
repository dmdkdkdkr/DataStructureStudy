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

	pList->ShellSort();
	pList->Display();
	pList->Clear();

	pList->AddToLast(80);
	pList->AddToLast(50);
	pList->AddToLast(70);
	pList->AddToLast(10);
	pList->AddToLast(60);
	pList->AddToLast(20);
	pList->AddToLast(40);
	pList->AddToLast(30);
	pList->Display();

	pList->ShellSort();
	pList->Display();

	delete pList;
	return 0;
}