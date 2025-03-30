#include <stdio.h>
#include "SelfBalancingBST_Factory.h"

int main()
{
	SelfBalancingBST<int>* pTree = SelfBanlancingBST_Factory<int>::Create(RED_BLACK);
	pTree->Insert(20);
	pTree->Insert(10);
	pTree->Insert(50);
	pTree->Insert(30);
	pTree->Insert(80);
	pTree->Insert(40);
	pTree->Insert(35);
	pTree->Insert(25);
	pTree->Insert(5);
	pTree->Insert(15);
	pTree->Insert(33);
	pTree->Insert(37);
	pTree->Insert(45);
	pTree->Insert(2);
	pTree->Insert(27);
	pTree->Display();

	pTree->Remove(15);
	pTree->Remove(33);
	pTree->Remove(37);
	pTree->Remove(35);
	pTree->Remove(25);
	pTree->Remove(27);
	pTree->Remove(2);
	pTree->Display();

	delete pTree;
	return 0;
}