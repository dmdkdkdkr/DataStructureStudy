#include <stdio.h>
#include "AVLBinarySearchTree.h"

int main()
{
	AVLBinarySearchTree<int>* pTree = new AVLBinarySearchTree<int>();
	pTree->Insert(9);
	pTree->Insert(3);
	pTree->Insert(1);
	pTree->Insert(10);
	pTree->Insert(12);
	pTree->Insert(6);
	pTree->Insert(4);
	pTree->Insert(5);
	pTree->Display();

	auto pNode = pTree->Search(10);
	printf("Searched Data: %d\n", pNode->data);
	pTree->Search(100);

	pTree->Remove(9);
	pTree->Remove(10);
	pTree->Remove(5);
	pTree->Display();

	pTree->Clear();
	pTree->Display();

	pTree->Insert(10);
	pTree->Insert(12);
	pTree->Insert(6);
	pTree->Display();

	delete pTree;
	return 0;
}