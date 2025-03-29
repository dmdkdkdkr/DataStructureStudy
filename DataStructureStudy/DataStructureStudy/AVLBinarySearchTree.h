#pragma once
#include <cmath>
#include <limits>
#include "LinkedStack.h"
#include "LinkedQueue.h"
#include "SelfBalancingBST.h"

template<typename T>
class AVLTreeNode : public SelfBalancingTreeNode<T>
{
public:
	using SelfBalancingTreeNode<T>::data;

	int height;
	int balanceFactor;
	AVLTreeNode<T>* pLeft;
	AVLTreeNode<T>* pRight;

	AVLTreeNode();
};

template<typename T>
AVLTreeNode<T>::AVLTreeNode() : height(1), balanceFactor(0), pLeft(nullptr), pRight(nullptr) {}

template<typename T>
class AVLBinarySearchTree : public SelfBalancingBST<T>
{
	using SelfBalancingBST<T>::count;
	using SelfBalancingBST<T>::IsEmpty;

protected:
	AVLTreeNode<T>* pRoot;

public:
	AVLBinarySearchTree();
	~AVLBinarySearchTree();

	bool Insert(T data) override;
	bool Remove(T data) override;
	void Clear() override;
	SelfBalancingTreeNode<T>* Search(T data) const override;
	void Display() const;

protected:
	void BalanceTree(LinkedStack<AVLTreeNode<T>*>* pStack);
	SelfBalancingTreeNode<T>* RotateLL(SelfBalancingTreeNode<T>* pNode) override;
	SelfBalancingTreeNode<T>* RotateRR(SelfBalancingTreeNode<T>* pNode) override;
	void UpdateHeight(AVLTreeNode<T>* pNode);
	void ChangeChild(AVLTreeNode<T>* pParent, AVLTreeNode<T>* pNode, AVLTreeNode<T>* pChild);
};

template<typename T>
AVLBinarySearchTree<T>::AVLBinarySearchTree() : SelfBalancingBST<T>() {}

template<typename T>
AVLBinarySearchTree<T>::~AVLBinarySearchTree()
{
	Clear();
}

template<typename T>
bool AVLBinarySearchTree<T>::Insert(T data)
{
	AVLTreeNode<T>* pNewNode = new AVLTreeNode<T>();
	pNewNode->data = data;

	LinkedStack<AVLTreeNode<T>*>* pStack = new LinkedStack<AVLTreeNode<T>*>();
	AVLTreeNode<T>* pParent = pRoot;
	while (pParent != nullptr)
	{
		if (pParent->data == data)
		{
			printf("%d => 중복된 값을 가지는 데이터가 이미 있습니다.\n", data);
			delete pNewNode;
			delete pStack;
			return false;
		}

		pStack->Push(pParent);
		if (data < pParent->data)
		{
			if (pParent->pLeft != nullptr)
			{
				pParent = pParent->pLeft;
			}
			else
			{
				pParent->pLeft = pNewNode;
				break;
			}
		}
		else
		{
			if (pParent->pRight != nullptr)
			{
				pParent = pParent->pRight;
			}
			else
			{
				pParent->pRight = pNewNode;
				break;
			}
		}
	}

	if (pParent == nullptr)
		pRoot = pNewNode;
	else
		BalanceTree(pStack);
	count++;

	delete pStack;
	return true;
}

template<typename T>
bool AVLBinarySearchTree<T>::Remove(T data)
{
	LinkedStack<AVLTreeNode<T>*>* pStack = new LinkedStack<AVLTreeNode<T>*>();
	AVLTreeNode<T>* pDelNode = pRoot;
	AVLTreeNode<T>* pParent = nullptr;
	while (pDelNode != nullptr)
	{
		if (pDelNode->data == data)
		{
			AVLTreeNode<T>* pReplaceParent = pDelNode;
			AVLTreeNode<T>* pReplace = nullptr;

			if (pDelNode->pLeft == nullptr && pDelNode->pRight == nullptr)
			{
				// 단말 노드를 삭제하는 경우
				if (pParent == nullptr)
				{
					pRoot = nullptr;
				}
				else
				{
					if (pParent->pLeft == pDelNode)
						pParent->pLeft = nullptr;
					else
						pParent->pRight = nullptr;
				}
				delete pDelNode;
			}
			else
			{
				pStack->Push(pDelNode);

				AVLTreeNode<T>* pReplaceParent = pDelNode;
				AVLTreeNode<T>* pReplace = nullptr;
				if (pDelNode->pLeft != nullptr)
				{
					// 왼쪽 자식 노드가 있는 경우
					pReplace = pReplaceParent->pLeft;
					while (pReplace->pRight != nullptr)
					{
						pStack->Push(pReplace);
						pReplaceParent = pReplace;
						pReplace = pReplace->pRight;
					}

					if (pReplaceParent->pRight == pReplace) 
						pReplaceParent->pRight = pReplace->pLeft;
					else 
						pReplaceParent->pLeft = pReplace->pLeft;
					pDelNode->data = pReplace->data;
					delete pReplace;
				}
				else
				{
					// 오른쪽 자식 노드가 있는 경우
					pReplace = pReplaceParent->pRight;
					while (pReplace->pLeft != nullptr)
					{
						pStack->Push(pReplace);
						pReplaceParent = pReplace;
						pReplace = pReplace->pLeft;
					}

					if (pReplaceParent->pLeft == pReplace) 
						pReplaceParent->pLeft = pReplace->pRight;
					else 
						pReplaceParent->pRight = pReplace->pRight;
					pDelNode->data = pReplace->data;
					delete pReplace;
				}
			}

			BalanceTree(pStack);

			count--;
			delete pStack;
			return true;
		}

		pStack->Push(pDelNode);
		pParent = pDelNode;
		if (data < pDelNode->data)
			pDelNode = pDelNode->pLeft;
		else
			pDelNode = pDelNode->pRight;
	}

	printf("%d => 해당하는 값을 가지는 데이터가 없습니다.\n", data);
	delete pStack;
	return false;
}

template<typename T>
inline void AVLBinarySearchTree<T>::Clear()
{
	if (IsEmpty()) return;

	LinkedQueue<AVLTreeNode<T>*>* pQueue = new LinkedQueue<AVLTreeNode<T>*>();
	pQueue->Enqueue(pRoot);
	while (!pQueue->IsEmpty())
	{
		AVLTreeNode<T>* pNode = pQueue->Dequeue();
		if (pNode->pLeft != nullptr) pQueue->Enqueue(pNode->pLeft);
		if (pNode->pRight != nullptr) pQueue->Enqueue(pNode->pRight);
		delete pNode;
	}
	delete pQueue;

	count = 0;
	pRoot = nullptr;
}

template<typename T>
SelfBalancingTreeNode<T>* AVLBinarySearchTree<T>::Search(T data) const
{
	if (IsEmpty())
	{
		printf("트리가 비었습니다. \n");
		return nullptr;
	}

	AVLTreeNode<T>* pNode = pRoot;
	while (pNode != nullptr)
	{
		if (pNode->data == data)
			return (SelfBalancingTreeNode<T>*)pNode;
		else if (data < pNode->data)
			pNode = pNode->pLeft;
		else
			pNode = pNode->pRight;
	}

	printf("%d => 해당하는 데이터가 트리에 존재하지 않습니다!\n", data);
	return nullptr;
}

template<typename T>
void AVLBinarySearchTree<T>::Display() const
{
	printf("\nDisplay avl binary search tree => count: %d\n", count);

	if (!IsEmpty())
	{
		LinkedQueue<AVLTreeNode<T>*>* pNodeQueue = new LinkedQueue<AVLTreeNode<T>*>();
		LinkedQueue<int>* pLvQueue = new LinkedQueue<int>();
		pNodeQueue->Enqueue(pRoot);
		pLvQueue->Enqueue(0);
		while (!pNodeQueue->IsEmpty())
		{
			AVLTreeNode<T>* pNode = pNodeQueue->Dequeue();
			int lv = pLvQueue->Dequeue();
			for (int i = 0; i < lv; i++) printf("\t");
			printf("[lv:%d] => data: %d, height:%d, balanceFactor: %d\n", lv, pNode->data, pNode->height, pNode->balanceFactor);

			if (pNode->pLeft != nullptr)
			{
				pNodeQueue->Enqueue(pNode->pLeft);
				pLvQueue->Enqueue(lv + 1);
			}
			if (pNode->pRight != nullptr)
			{
				pNodeQueue->Enqueue(pNode->pRight);
				pLvQueue->Enqueue(lv + 1);
			}
		}
		delete pLvQueue;
		delete pNodeQueue;
	}

	printf("End displaying avl binary search tree\n");
}

template<typename T>
void AVLBinarySearchTree<T>::BalanceTree(LinkedStack<AVLTreeNode<T>*>* pStack)
{
	AVLTreeNode<T>* pNode = nullptr;
	while (!pStack->IsEmpty())
	{
		pNode = pStack->Pop();
		UpdateHeight(pNode);

		int balanceFactor = pNode->balanceFactor;
		if (std::abs(balanceFactor) <= 1) continue;

		AVLTreeNode<T>* pParent = (pStack->IsEmpty()) ? nullptr : pStack->Peek();
		AVLTreeNode<T>* pChild = nullptr;
		if (balanceFactor == 2 && pNode->pLeft->balanceFactor == 1)
		{
			// LL
			pChild = (AVLTreeNode<T>*)RotateLL(pNode);
			ChangeChild(pParent, pNode, pChild);
		}
		else if (balanceFactor == 2 && pNode->pLeft->balanceFactor == -1)
		{
			// LR
			pNode->pLeft = (AVLTreeNode<T>*)RotateRR(pNode->pLeft);
			pChild = (AVLTreeNode<T>*)RotateLL(pNode);
			ChangeChild(pParent, pNode, pChild);
		}
		else if (balanceFactor == -2 && pNode->pRight->balanceFactor == 1)
		{
			// RL
			pNode->pRight = (AVLTreeNode<T>*)RotateLL(pNode->pRight);
			pChild = (AVLTreeNode<T>*)RotateRR(pNode);
			ChangeChild(pParent, pNode, pChild);
		}
		else if (balanceFactor == -2 && pNode->pRight->balanceFactor == -1)
		{
			// RR
			pChild = (AVLTreeNode<T>*)RotateRR(pNode);
			ChangeChild(pParent, pNode, pChild);
		}
	}
}

template<typename T>
SelfBalancingTreeNode<T>* AVLBinarySearchTree<T>::RotateLL(SelfBalancingTreeNode<T>* pNode)
{
	AVLTreeNode<T>* pCur = (AVLTreeNode<T>*)pNode;
	AVLTreeNode<T>* pLeft = pCur->pLeft;
	pCur->pLeft = pLeft->pRight;
	pLeft->pRight = pCur;

	UpdateHeight(pCur);
	UpdateHeight(pLeft);

	return (SelfBalancingTreeNode<T>*)pLeft;
}

template<typename T>
SelfBalancingTreeNode<T>* AVLBinarySearchTree<T>::RotateRR(SelfBalancingTreeNode<T>* pNode)
{
	AVLTreeNode<T>* pCur = (AVLTreeNode<T>*)pNode;
	AVLTreeNode<T>* pRight = pCur->pRight;
	pCur->pRight = pRight->pLeft;
	pRight->pLeft = pCur;

	UpdateHeight(pCur);
	UpdateHeight(pRight);

	return (SelfBalancingTreeNode<T>*)pRight;
}

template<typename T>
void AVLBinarySearchTree<T>::UpdateHeight(AVLTreeNode<T>* pNode)
{
	int leftHeight = (pNode->pLeft != nullptr) ? pNode->pLeft->height : 0;
	int rightHeight = (pNode->pRight != nullptr) ? pNode->pRight->height : 0;
	int balanceFactor = leftHeight - rightHeight;
	pNode->height = (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
	pNode->balanceFactor = balanceFactor;
}

template<typename T>
void AVLBinarySearchTree<T>::ChangeChild(AVLTreeNode<T>* pParent, AVLTreeNode<T>* pNode, AVLTreeNode<T>* pChild)
{
	if (pParent == nullptr)
	{
		pRoot = pChild;
	}
	else
	{
		if (pParent->pLeft == pNode) pParent->pLeft = pChild;
		if (pParent->pRight == pNode) pParent->pRight = pChild;
	}
}