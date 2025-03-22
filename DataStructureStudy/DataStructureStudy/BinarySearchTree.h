#pragma once

#include <stdio.h>
#include <tuple>
#include "LinkedBinaryTreeNode.h"
#include "LinkedStack.h"

template <typename T>
class BinarySearchTree
{
private:
	int count;
	LinkedBinaryTreeNode<T>* pRoot;

public:
	BinarySearchTree<T>();
	~BinarySearchTree<T>();

	bool Insert(T _key);
	bool Remove(T _key);
	void Clear();
	LinkedBinaryTreeNode<T>* Search(T _key);
	void Display();
	int Count();
	bool IsEmpty();
};

template<typename T>
BinarySearchTree<T>::BinarySearchTree() : count(0), pRoot(NULL) {}

template<typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
	printf("~BinarySearchTree is called\n");
	Clear();
}

template<typename T>
bool BinarySearchTree<T>::Insert(T _key)
{
	LinkedBinaryTreeNode<T>* pParent = pRoot;
	LinkedBinaryTreeNode<T>* pNew = new LinkedBinaryTreeNode<T>(_key);

	if (IsEmpty())
	{
		pRoot = pNew;
	}
	else
	{
		while (pParent != NULL)
		{
			int _parentData = pParent->data;
			if (_key == _parentData)
			{
				printf("Same key is already added\n");
				return false;
			}
			else
			{
				if (_key < _parentData)
				{
					if (pParent->pLeft == NULL)
					{
						pParent->pLeft = pNew;
						break;
					}
					else
					{
						pParent = pParent->pLeft;
					}
				}
				else
				{
					if (pParent->pRight == NULL)
					{
						pParent->pRight = pNew;
						break;
					}
					else
					{
						pParent = pParent->pRight;
					}
				}
			}
		}
	}
	count++;

	return true;
}

template<typename T>
bool BinarySearchTree<T>::Remove(T _key)
{
	if (IsEmpty())
	{
		printf("BinarySearchTree is empty\n");
		return false;
	}

	LinkedBinaryTreeNode<T>* pParent = NULL;
	LinkedBinaryTreeNode<T>* pDel = pRoot;
	LinkedBinaryTreeNode<T>* pReplace = NULL;

	while (pDel != NULL)
	{
		int _nodeKey = pDel->data;
		if (_key == _nodeKey)
		{
			// Enter removing sequence
			if (pDel->pLeft == NULL && pDel->pRight == NULL)
			{
				// Delete leaf node
				if (pParent == NULL)
				{
					pRoot = NULL;
				}
				else
				{
					if (pParent->pLeft == pDel)
						pParent->pLeft = NULL;
					else
						pParent->pRight = NULL;
				}

				delete pDel;
				break;
			}
			else if (pDel->pLeft != NULL)
			{
				// Delete node that have left child.
				pParent = pDel;
				pReplace = pParent->pLeft;
				while (pReplace->pRight != NULL)
				{
					pParent = pReplace;
					pReplace = pReplace->pRight;
				}

				if (pParent->pLeft == pReplace)
					pParent->pLeft = pReplace->pLeft;
				else
					pParent->pRight = pReplace->pLeft;
				pDel->data = pReplace->data;
				delete pReplace;
				break;
			}
			else if (pDel->pRight != NULL)
			{
				// Delete node that have right child.
				pParent = pDel;
				pReplace = pParent->pRight;
				while (pReplace->pLeft != NULL)
				{
					pParent = pReplace;
					pReplace = pReplace->pLeft;
				}

				if (pParent->pRight == pReplace)
					pParent->pRight = pReplace->pRight;
				else
					pParent->pLeft = pReplace->pRight;
				pDel->data = pReplace->data;
				delete pReplace;
				break;
			}
		}
		else
		{
			// Enter moving sequence
			pParent = pDel;
			if (_key < _nodeKey) 
				pDel = pDel->pLeft;
			else 
				pDel = pDel->pRight;
		}
	}

	if (pDel == NULL)
	{
		printf("Can't find the node that have same key\n");
		return false;
	}
	count--;

	return true;
}

template<typename T>
inline void BinarySearchTree<T>::Clear()
{
	if (IsEmpty()) return;

	LinkedStack<LinkedBinaryTreeNode<T>*>* pStack = new LinkedStack<LinkedBinaryTreeNode<T>*>();
	pStack->Push(pRoot);

	LinkedBinaryTreeNode<T>* pDel = NULL;
	while (!pStack->IsEmpty())
	{
		pDel = pStack->Pop();
		if (pDel->pRight != NULL) pStack->Push(pDel->pRight);
		if (pDel->pLeft != NULL) pStack->Push(pDel->pLeft);
		delete pDel;
	}

	count = 0;
	pRoot = NULL;

	delete pStack;

	return;
}

template<typename T>
LinkedBinaryTreeNode<T>* BinarySearchTree<T>::Search(T _key)
{
	LinkedBinaryTreeNode<T>* pNode = pRoot;

	if (IsEmpty())
	{
		printf("BinarySearchTree is empty\n");
		return NULL;
	}

	while (pNode != NULL)
	{
		T nodeKey = pNode->data;
		if (_key == nodeKey)
		{
			break;
		}
		else
		{
			if (_key < nodeKey)
				pNode = pNode->pLeft;
			else
				pNode = pNode->pRight;
		}
	}

	return pNode;
}

template<typename T>
void BinarySearchTree<T>::Display()
{
	typedef std::tuple<int, LinkedBinaryTreeNode<T>*> Tuple;

	printf("\nDisplay binary search tree => count: %d\n", count);
	
	LinkedStack<Tuple>* pStack = new LinkedStack<Tuple>();
	if (pRoot != NULL) pStack->Push(std::make_tuple(0, pRoot));
	while (!pStack->IsEmpty())
	{
		Tuple tuple = pStack->Pop();
		int lv = std::get<0>(tuple);
		LinkedBinaryTreeNode<T>* pNode = std::get<1>(tuple);

		for (int i = 0; i < lv; i++) printf("\t");
		printf("[Lv:%d] => data: %d\n", lv, pNode->data);

		if (pNode->pRight != NULL) pStack->Push(std::make_tuple(lv + 1, pNode->pRight));
		if (pNode->pLeft != NULL) pStack->Push(std::make_tuple(lv + 1, pNode->pLeft));
	}

	printf("End displaying binary search tree\n");

	delete pStack;
}

template<typename T>
inline int BinarySearchTree<T>::Count() { return count; }

template<typename T>
inline bool BinarySearchTree<T>::IsEmpty() { return (count == 0); }