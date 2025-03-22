#pragma once
#include <stdio.h>
#include <tuple>

#include "LinkedBinaryTreeNode.h"
#include "LinkedStack.h";
#include "LinkedQueue.h";

template <typename T>
class LinkedBinaryTree
{
private:
	int count;
	LinkedBinaryTreeNode<T>* pRoot;

public:
	LinkedBinaryTree();
	~LinkedBinaryTree();

	bool InserNodeToRoot(T data);
	bool InsertNodeToLeft(LinkedBinaryTreeNode<T>* pParent, T data);
	bool InsertNodeToRight(LinkedBinaryTreeNode<T>* pParent, T data);
	LinkedBinaryTreeNode<T>* GetRootNode();
	LinkedBinaryTreeNode<T>* GetLeftChildNode(LinkedBinaryTreeNode<T>* pParent);
	LinkedBinaryTreeNode<T>* GetRightChildNode(LinkedBinaryTreeNode<T>* pParent);
	void Clear();
	bool Copy(LinkedBinaryTree<T>* pSrc);
	bool Equal(LinkedBinaryTree<T>* pOtherTree);
	int LeafCount();
	int Height();
	void DisplayByPreorder();
	void DisplayByInorder();
	void DisplayByPostorder();
	void DisplayByLevel();
	void DisplayPretty();
	int Count();
	bool IsEmpty();
};

template<typename T>
LinkedBinaryTree<T>::LinkedBinaryTree() : count(0), pRoot(NULL) {}

template<typename T>
LinkedBinaryTree<T>::~LinkedBinaryTree()
{
	printf("~LinkedBinaryTree is called\n");
	Clear();
}

template<typename T>
bool LinkedBinaryTree<T>::InserNodeToRoot(T data)
{
	if (pRoot != NULL)
	{
		printf("Root is already inserted\n");
		return false;
	}

	auto pNew = new LinkedBinaryTreeNode<T>(data);
	pRoot = pNew;
	count++;

	return true;
}

template<typename T>
bool LinkedBinaryTree<T>::InsertNodeToLeft(LinkedBinaryTreeNode<T>* pParent, T data)
{
	if (pParent == NULL)
	{
		printf("Parent node is NULL\n");
		return false;
	}

	if (pParent->pLeft != NULL)
	{
		printf("Left child is already inserted\n");
		return false;
	}

	auto pNew = new LinkedBinaryTreeNode<T>(data);
	pParent->pLeft = pNew;
	count++;

	return true;
}

template<typename T>
bool LinkedBinaryTree<T>::InsertNodeToRight(LinkedBinaryTreeNode<T>* pParent, T data)
{
	if (pParent == NULL)
	{
		printf("Parent node is NULL\n");
		return false;
	}

	if (pParent->pRight != NULL)
	{
		printf("Right child is already inserted\n");
		return false;
	}

	auto pNew = new LinkedBinaryTreeNode<T>(data);
	pParent->pRight = pNew;
	count++;

	return true;
}

template<typename T>
LinkedBinaryTreeNode<T>* LinkedBinaryTree<T>::GetRootNode()
{
	if (IsEmpty())
	{
		printf("Tree is empty\n");
		return NULL;
	}

	return pRoot;
}

template<typename T>
LinkedBinaryTreeNode<T>* LinkedBinaryTree<T>::GetLeftChildNode(LinkedBinaryTreeNode<T>* pParent)
{
	if (pParent == NULL)
	{
		printf("Parent node is NULL\n");
		return NULL;
	}

	if (pParent->pLeft == NULL)
	{
		printf("Left child wasn't inserted\n");
		return NULL;
	}

	return pParent->pLeft;
}

template<typename T>
LinkedBinaryTreeNode<T>* LinkedBinaryTree<T>::GetRightChildNode(LinkedBinaryTreeNode<T>* pParent)
{
	if (pParent == NULL)
	{
		printf("Parent node is NULL\n");
		return NULL;
	}

	if (pParent->pRight == NULL)
	{
		printf("Right child wasn't inserted\n");
		return NULL;
	}

	return pParent->pRight;
}

template<typename T>
void LinkedBinaryTree<T>::Clear()
{
	if (IsEmpty()) return;

	LinkedBinaryTreeNode<T>* pDel = NULL;
	LinkedBinaryTreeNode<T>* pLeft = NULL;
	LinkedBinaryTreeNode<T>* pRight = NULL;

	LinkedStack<LinkedBinaryTreeNode<T>*>* pStack = new LinkedStack<LinkedBinaryTreeNode<T>*>();
	pStack->Push(pRoot);
	while (pStack->Count() > 0)
	{
		pDel = pStack->Pop();
		pLeft = pDel->pLeft;
		pRight = pDel->pRight;

		delete pDel;
		if (pRight != NULL) pStack->Push(pRight);
		if (pLeft != NULL) pStack->Push(pLeft);
	}
	delete pStack;

	count = 0;
	pRoot = NULL;
}

template<typename T>
bool LinkedBinaryTree<T>::Copy(LinkedBinaryTree<T>* pSrc)
{
	if (pSrc == NULL)
	{
		printf("pSrc is NULL\n");
		return false;
	}

	Clear();
	if (pSrc->IsEmpty()) return true;

	LinkedBinaryTreeNode<T>* pSrcNode = pSrc->pRoot;
	LinkedBinaryTreeNode<T>* pDstNode = new LinkedBinaryTreeNode<T>(pSrcNode->data);
	pRoot = pDstNode;

	LinkedStack<LinkedBinaryTreeNode<T>*>* pStack = new LinkedStack<LinkedBinaryTreeNode<T>*>();
	pStack->Push(pDstNode);
	pStack->Push(pSrcNode);

	while (!pStack->IsEmpty())
	{
		pSrcNode = pStack->Pop();
		pDstNode = pStack->Pop();

		if (pSrcNode->pRight != NULL)
		{
			pDstNode->pRight = new LinkedBinaryTreeNode<T>(pSrcNode->pRight->data);
			pStack->Push(pDstNode->pRight);
			pStack->Push(pSrcNode->pRight);
		}

		if (pSrcNode->pLeft != NULL)
		{
			pDstNode->pLeft = new LinkedBinaryTreeNode<T>(pSrcNode->pLeft->data);
			pStack->Push(pDstNode->pLeft);
			pStack->Push(pSrcNode->pLeft);
		}
	}
	count = pSrc->Count();

	delete pStack;
	return true;
}

template<typename T>
bool LinkedBinaryTree<T>::Equal(LinkedBinaryTree<T>* pOtherTree)
{
	if (pOtherTree == NULL) return false;
	if (IsEmpty() && pOtherTree->IsEmpty()) return true;
	if (IsEmpty() || pOtherTree->IsEmpty()) return false;

	LinkedBinaryTreeNode<T>* pMine = pRoot;
	LinkedBinaryTreeNode<T>* pOther = pOtherTree->pRoot;

	LinkedStack<LinkedBinaryTreeNode<T>*>* pStack = new LinkedStack<LinkedBinaryTreeNode<T>*>();
	pStack->Push(pOther);
	pStack->Push(pMine);

	while (!pStack->IsEmpty())
	{
		pMine = pStack->Pop();
		pOther = pStack->Pop();

		if (pMine->data != pOther->data) return false;

		if (pMine->pRight != NULL && pOther->pRight != NULL)
		{
			pStack->Push(pOther->pRight);
			pStack->Push(pMine->pRight);
		}
		else if (pMine->pRight != NULL || pOther->pRight != NULL)
		{
			return false;
		}

		if (pMine->pLeft != NULL && pOther->pLeft != NULL)
		{
			pStack->Push(pOther->pLeft);
			pStack->Push(pMine->pLeft);
		}
		else if (pMine->pLeft != NULL || pOther->pLeft != NULL)
		{
			return false;
		}
	}

	delete pStack;
	return true;
}

template<typename T>
int LinkedBinaryTree<T>::LeafCount()
{
	int cnt = 0;
	if (IsEmpty()) return cnt;

	LinkedBinaryTreeNode<T>* pNode = NULL;
	LinkedBinaryTreeNode<T>* pLeft = NULL;
	LinkedBinaryTreeNode<T>* pRight = NULL;

	LinkedStack<LinkedBinaryTreeNode<T>*>* pStack = new LinkedStack<LinkedBinaryTreeNode<T>*>();
	if (pRoot != NULL) pStack->Push(pRoot);

	while (pStack->Count() > 0)
	{
		pNode = pStack->Pop();
		pLeft = pNode->pLeft;
		pRight = pNode->pRight;

		if (pLeft == NULL && pRight == NULL) cnt++;
		
		if (pRight != NULL) pStack->Push(pRight);
		if (pLeft != NULL) pStack->Push(pLeft);
	}

	delete pStack;
	return cnt;
}

template<typename T>
int LinkedBinaryTree<T>::Height()
{
	typedef std::tuple<int, LinkedBinaryTreeNode<T>*> HeightTuple;

	int maxHeight = 0;
	if (IsEmpty()) return maxHeight;

	int height = 1;
	LinkedBinaryTreeNode<T>* pNode = NULL;

	HeightTuple tuple;
	LinkedQueue<HeightTuple>* pQueue = new LinkedQueue<HeightTuple>();
	if (pRoot != NULL) pQueue->Enqueue(std::make_tuple(height, pRoot));

	while (!pQueue->IsEmpty())
	{
		tuple = pQueue->Dequeue();
		height = std::get<0>(tuple);
		pNode = std::get<1>(tuple);

		if (height > maxHeight) maxHeight = height;

		if (pNode->pLeft != NULL) pQueue->Enqueue(std::make_tuple(height + 1, pNode->pLeft));
		if (pNode->pRight != NULL) pQueue->Enqueue(std::make_tuple(height + 1, pNode->pRight));
	}

	delete pQueue;
	return maxHeight;
}

template<typename T>
void LinkedBinaryTree<T>::DisplayByPreorder()
{
	printf("\nDisplay LinkedBinaryTree by preorder => Count: %d\n", count);

	LinkedBinaryTreeNode<T>* pNode = NULL;
	LinkedBinaryTreeNode<T>* pLeft = NULL;
	LinkedBinaryTreeNode<T>* pRight = NULL;

	LinkedStack<LinkedBinaryTreeNode<T>*>* pStack = new LinkedStack<LinkedBinaryTreeNode<T>*>();
	if (pRoot != NULL) pStack->Push(pRoot);

	while (pStack->Count() > 0)
	{
		pNode = pStack->Pop();
		pLeft = pNode->pLeft;
		pRight = pNode->pRight;

		printf("\tData: %d\n", pNode->data);
		if (pRight != NULL) pStack->Push(pRight);
		if (pLeft != NULL) pStack->Push(pLeft);
	}

	printf("End displaying LinkedBinaryTree\n");
	delete pStack;
}

template<typename T>
void LinkedBinaryTree<T>::DisplayByInorder()
{
	printf("\nDisplay LinkedBinaryTree by inorder => Count: %d\n", count);

	LinkedBinaryTreeNode<T>* pNode = NULL;

	LinkedStack<LinkedBinaryTreeNode<T>*>* pStack = new LinkedStack<LinkedBinaryTreeNode<T>*>();
	if (pRoot != NULL) pStack->Push(pRoot);

	while (!pStack->IsEmpty())
	{
		pNode = pStack->Pop();
		while (pNode != NULL)
		{
			pStack->Push(pNode);
			pNode = pNode->pLeft;
		}

		while (!pStack->IsEmpty())
		{
			pNode = pStack->Pop();
			printf("\tData: %d\n", pNode->data);
			if (pNode->pRight != NULL)
			{
				pStack->Push(pNode->pRight);
				break;
			}
		}
	}

	printf("End displaying LinkedBinaryTree\n");
	delete pStack;
}

template<typename T>
void LinkedBinaryTree<T>::DisplayByPostorder()
{
	printf("\nDisplay LinkedBinaryTree by postorder => Count: %d\n", count);

	LinkedBinaryTreeNode<T>* pNode = NULL;
	LinkedBinaryTreeNode<T>* pNext = NULL;
	LinkedBinaryTreeNode<T>* pChildNode = NULL;

	LinkedStack<LinkedBinaryTreeNode<T>*>* pStack = new LinkedStack<LinkedBinaryTreeNode<T>*>();
	if (pRoot != NULL) pStack->Push(pRoot);

	while (!pStack->IsEmpty())
	{
		while (!pStack->IsEmpty())
		{
			pNode = pStack->Pop();
			if (pNode->pRight == NULL && pNode->pLeft == NULL)
			{
				pStack->Push(pNode);
				break;
			}
			else
			{
				pStack->Push(pNode);
				if (pNode->pRight != NULL)
				{
					pNext = pNode->pRight;
					pStack->Push(pNext);
				}
				if (pNode->pLeft != NULL)
				{
					pNext = pNode->pLeft;
					pStack->Push(pNext);
				}
				pNode = pNext;
			}
		}

		while (!pStack->IsEmpty())
		{
			pNode = pStack->Pop();
			if (pNode->pRight == NULL && pNode->pLeft == NULL)
			{
				printf("\tData: %d\n", pNode->data);
				pChildNode = pNode;
			}
			else
			{
				if (pNode->pRight != NULL)
				{
					if (pNode->pRight == pChildNode)
					{
						printf("\tData: %d\n", pNode->data);
						pChildNode = pNode;
					}
					else
					{
						pStack->Push(pNode);
						break;
					}
				}
				else if (pNode->pLeft != NULL)
				{
					if (pNode->pLeft == pChildNode)
					{
						printf("\tData: %d\n", pNode->data);
						pChildNode = pNode;
					}
					else
					{
						pStack->Push(pNode);
						break;
					}
				}
			}
		}
	}

	printf("End displaying LinkedBinaryTree\n");
	delete pStack;
}

template<typename T>
void LinkedBinaryTree<T>::DisplayByLevel()
{
	printf("\nDisplay LinkedBinaryTree by level => Count: %d\n", count);

	LinkedBinaryTreeNode<T>* pNode = NULL;

	LinkedQueue<LinkedBinaryTreeNode<T>*>* pQueue = new LinkedQueue<LinkedBinaryTreeNode<T>*>();
	if (pRoot != NULL) pQueue->Enqueue(pRoot);
	
	while (!pQueue->IsEmpty())
	{
		pNode = pQueue->Dequeue();
		printf("\tData: %d\n", pNode->data);
		if (pNode->pLeft != NULL) pQueue->Enqueue(pNode->pLeft);
		if (pNode->pRight != NULL) pQueue->Enqueue(pNode->pRight);
	}

	printf("End displaying LinkedBinaryTree\n");
	delete pQueue;
}

template<typename T>
void LinkedBinaryTree<T>::DisplayPretty()
{
	printf("\nDisplay LinkedBinaryTree => Count: %d\n", count);

	typedef std::tuple<int, LinkedBinaryTreeNode<T>*> Tuple;

	int level = 1;
	Tuple tuple;

	LinkedBinaryTreeNode<T>* pNode = NULL;
	LinkedBinaryTreeNode<T>* pLeft = NULL;
	LinkedBinaryTreeNode<T>* pRight = NULL;

	LinkedStack<Tuple>* pStack = new LinkedStack<Tuple>();
	if (pRoot != NULL)
		pStack->Push(std::make_tuple(level, pRoot));

	while (!pStack->IsEmpty())
	{
		tuple = pStack->Pop();

		level = std::get<0>(tuple);
		pNode = std::get<1>(tuple);
		pLeft = pNode->pLeft;
		pRight = pNode->pRight;

		for (int i = 1; i < level; i++) printf("\t");
		printf("[Lv:%d] => Data: %d\n", level, pNode->data);

		if (pRight != NULL)
		{
			pStack->Push(std::make_tuple(level + 1, pRight));
		}

		if (pLeft != NULL)
		{
			pStack->Push(std::make_tuple(level + 1, pLeft));
		}
	}

	printf("End displaying LinkedBinaryTree\n");
	delete pStack;
}

template<typename T>
inline int LinkedBinaryTree<T>::Count()
{
	return count;
}

template<typename T>
inline bool LinkedBinaryTree<T>::IsEmpty()
{
	return count == 0;
}
