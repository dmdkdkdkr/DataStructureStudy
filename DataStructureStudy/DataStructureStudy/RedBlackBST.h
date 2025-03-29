#pragma once
#include "SelfBalancingBST.h"

enum RedBlackType
{
	RED,
	BLACK
};

template<typename T>
class RedBlackTreeNode : public SelfBalancingTreeNode<T>
{
public:
	using SelfBalancingTreeNode<T>::data;

	RedBlackType type;
	RedBlackTreeNode<T>* pParent;
	RedBlackTreeNode<T>* pLeft;
	RedBlackTreeNode<T>* pRight;

	RedBlackTreeNode();
};

template<typename T>
RedBlackTreeNode<T>::RedBlackTreeNode() : type(RED), pParent(nullptr), pLeft(nullptr), pRight(nullptr) {}


template<typename T>
class RedBlackBST : public SelfBalancingBST<T>
{
private:
	using SelfBalancingBST<T>::count;
	using SelfBalancingBST<T>::IsEmpty;

	RedBlackTreeNode<T>* pRoot;

public:
	RedBlackBST();
	~RedBlackBST();

	bool Insert(T data) override;
	bool Remove(T data) override;
	void Clear() override;
	SelfBalancingTreeNode<T>* Search(T data) const override;
	void Display() const override;

protected:
	SelfBalancingTreeNode<T>* RotateLL(SelfBalancingTreeNode<T>* pNode) override;
	SelfBalancingTreeNode<T>* RotateRR(SelfBalancingTreeNode<T>* pNode) override;

private:
	void SolveInsertionImbalance(RedBlackTreeNode<T>* pNode);
	void SolveRemovalImbalance(RedBlackTreeNode<T>* pNode);

	RedBlackType GetColor(RedBlackTreeNode<T>* pNode) const;
	RedBlackType ReverseColor(RedBlackType type) const;
};

template<typename T>
RedBlackBST<T>::RedBlackBST() : SelfBalancingBST<T>() {}

template<typename T>
RedBlackBST<T>::~RedBlackBST() { Clear(); }

template<typename T>
bool RedBlackBST<T>::Insert(T data)
{
	RedBlackTreeNode<T>* pNew = new RedBlackTreeNode<T>();
	pNew->data = data;

	RedBlackTreeNode<T>* pNode = pRoot;
	RedBlackTreeNode<T>* pParent = nullptr;
	while (pNode != nullptr)
	{
		if (pNode->data == data)
		{
			printf("%d => 이미 같은 값을 가진 데이터가 있습니다. [RedBlackBST<T>::Insert(T data)]\n", data);
			delete pNew;
			return false;
		}

		pParent = pNode;
		if (data < pNode->data)
		{
			if (pNode->pLeft != nullptr)
			{
				pNode = pNode->pLeft;
			}
			else
			{
				pNew->pParent = pParent;
				pParent->pLeft = pNew;
				break;
			}
		}
		else
		{
			if (pNode->pRight != nullptr)
			{
				pNode = pNode->pRight;
			}
			else
			{
				pNew->pParent = pParent;
				pParent->pRight = pNew;
				break;
			}
		}
	}
	if (pParent == nullptr) pRoot = pNew;
	count++;

	SolveInsertionImbalance(pNew);

	return true;
}

template<typename T>
bool RedBlackBST<T>::Remove(T data)
{
	if (IsEmpty()) return false;

	RedBlackTreeNode<T>* pDel = pRoot;
	RedBlackTreeNode<T>* pDelParent = nullptr;
	while (pDel != nullptr)
	{
		if (pDel->data == data) break;

		pDelParent = pDel;
		if (data < pDel->data)
			pDel = pDel->pLeft;
		else
			pDel = pDel->pRight;
	}
	if (pDel == nullptr)
	{
		printf("%d => 해당하는 데이터가 트리 내에 없습니다. [#Remove(T data)]\n", data);
		return false;
	}

	if (pDel->pLeft == nullptr && pDel->pRight == nullptr)
	{
		if (pDelParent == nullptr)
		{
			pRoot = nullptr;
		}
		else
		{
			if (pDelParent->pLeft == pDel) pDelParent->pLeft = nullptr;
			if (pDelParent->pRight == pDel) pDelParent->pRight = nullptr;
			SolveRemovalImbalance(pDel);
		}
		delete pDel;
	}
	else
	{
		RedBlackTreeNode<T>* pReplace = nullptr;
		RedBlackTreeNode<T>* pReplaceParent = pDel;
		RedBlackTreeNode<T>* pReplaceChild = nullptr;
		if (pDel->pLeft != nullptr)
		{
			pReplace = pReplaceParent->pLeft;
			while (pReplace->pRight != nullptr)
			{
				pReplaceParent = pReplace;
				pReplace = pReplace->pRight;
			}
			pReplaceChild = pReplace->pLeft;
			if (pReplaceChild != nullptr) pReplaceChild->pParent = pReplaceParent;
			if (pReplaceParent->pLeft == pReplace) pReplaceParent->pLeft = pReplaceChild;
			if (pReplaceParent->pRight == pReplace) pReplaceParent->pRight = pReplaceChild;
		}
		else
		{
			pReplace = pReplaceParent->pRight;
			while (pReplace->pLeft != nullptr)
			{
				pReplaceParent = pReplace;
				pReplace = pReplace->pLeft;
			}
			pReplaceChild = pReplace->pRight;
			if (pReplaceChild != nullptr) pReplaceChild->pParent = pReplaceParent;
			if (pReplaceParent->pLeft == pReplace) pReplaceParent->pLeft = pReplaceChild;
			if (pReplaceParent->pRight == pReplace) pReplaceParent->pRight = pReplaceChild;
		}
		pDel->data = pReplace->data;
		SolveRemovalImbalance(pReplace);
		delete pReplace;
	}
	count--;

	return true;
}

template<typename T>
void RedBlackBST<T>::Clear()
{
	if (IsEmpty()) return;

	LinkedQueue<RedBlackTreeNode<T>*>* pQueue = new LinkedQueue<RedBlackTreeNode<T>*>();
	pQueue->Enqueue(pRoot);
	while (!pQueue->IsEmpty())
	{
		RedBlackTreeNode<T>* pNode = pQueue->Dequeue();
		if (pNode->pLeft != nullptr) pQueue->Enqueue(pNode->pLeft);
		if (pNode->pRight != nullptr) pQueue->Enqueue(pNode->pRight);
		delete pNode;
	}
	count = 0;
	pRoot = nullptr;
	delete pQueue;
}

template<typename T>
SelfBalancingTreeNode<T>* RedBlackBST<T>::Search(T data) const
{
	if (IsEmpty())
	{
		printf("트리가 비었습니다. [RedBlackBST<T>::Search(T data)]\n");
		return nullptr;
	}

	RedBlackTreeNode<T>* pNode = pRoot;
	while (pNode != nullptr)
	{
		if (pNode->data == data) return (SelfBalancingTreeNode<T>*)pNode;
		else if (data < pNode->data) pNode = pNode->pLeft;
		else pNode = pNode->pRight;
	}

	printf("%d => 해당하는 데이터를 찾을 수 없습니다. [RedBlackBST<T>::Search(T data)]\n", data);
	return nullptr;
}

template<typename T>
void RedBlackBST<T>::Display() const
{
	printf("\nDisplay red-black binary search tree => count: %d\n", count);
	if (!IsEmpty())
	{
		LinkedQueue<RedBlackTreeNode<T>*>* pNodeQueue = new LinkedQueue<RedBlackTreeNode<T>*>();
		LinkedQueue<int>* pLvQueue = new LinkedQueue<int>();

		pNodeQueue->Enqueue(pRoot);
		pLvQueue->Enqueue(0);
		while (!pNodeQueue->IsEmpty())
		{
			RedBlackTreeNode<T>* pNode = pNodeQueue->Dequeue();
			int lv = pLvQueue->Dequeue();
			for (int i = 0; i < lv; i++) printf("\t");
			printf("[lv:%d] => type: %d, data: %d\n", lv, pNode->type, pNode->data);

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
	printf("End displaying red-black binary search tree\n");
}

template<typename T>
SelfBalancingTreeNode<T>* RedBlackBST<T>::RotateLL(SelfBalancingTreeNode<T>* pNode)
{
	RedBlackTreeNode<T>* pCur = (RedBlackTreeNode<T>*)pNode;
	RedBlackTreeNode<T>* pLeft = pCur->pLeft;
	RedBlackTreeNode<T>* pParent = pCur->pParent;

	pCur->pLeft = pLeft->pRight;
	pLeft->pRight = pCur;

	pLeft->pParent = pParent;
	pCur->pParent = pLeft;

	if (pParent == nullptr) return pLeft;
	if (pParent->pLeft == pCur)
		pParent->pLeft = pLeft;
	else
		pParent->pRight = pLeft;

	return pLeft;
}

template<typename T>
SelfBalancingTreeNode<T>* RedBlackBST<T>::RotateRR(SelfBalancingTreeNode<T>* pNode)
{
	RedBlackTreeNode<T>* pCur = (RedBlackTreeNode<T>*)pNode;
	RedBlackTreeNode<T>* pRight = pCur->pRight;
	RedBlackTreeNode<T>* pParent = pCur->pParent;

	pCur->pRight = pRight->pLeft;
	pRight->pLeft = pCur;

	pRight->pParent = pParent;
	pCur->pParent = pRight;

	if (pParent == nullptr) return pRight;
	if (pParent->pLeft == pCur)
		pParent->pLeft = pRight;
	else
		pParent->pRight = pRight;

	return pRight;
}

template<typename T>
void RedBlackBST<T>::SolveInsertionImbalance(RedBlackTreeNode<T>* pNode)
{
	RedBlackTreeNode<T>* pParent = nullptr, * pGrandParent = nullptr, *pUncle = nullptr;
	while (pNode != nullptr)
	{
		// 루트 노드 삽입 체크
		if (pNode == pRoot)
		{
			pNode->type = BLACK;
			return;
		}

		// 체크할 노드의 부모가 블랙이면 바로 리턴
		if (pNode->pParent->type == BLACK) return;

		// 부모, 삼촌, 조부모 노드를 각각 구한후 Recoloring을 해야하는지 체크한다.
		pParent = pNode->pParent;
		pGrandParent = pParent->pParent;
		pUncle = (pGrandParent->pLeft == pParent) ? pGrandParent->pRight : pGrandParent->pLeft;
		if (GetColor(pParent) != GetColor(pUncle)) break;

		// Recoloring
		pParent->type = BLACK;
		if (pUncle != nullptr) pUncle->type = BLACK;
		pGrandParent->type = RED;
		pNode = pGrandParent;
	}

	// Restructing
	if (pGrandParent->pLeft == pParent && pParent->pLeft == pNode)
	{
		// LL
		pParent->type = ReverseColor(pParent->type);
		pGrandParent->type = ReverseColor(pGrandParent->type);
		pNode = (RedBlackTreeNode<T>*)RotateLL(pGrandParent);
	}
	else if (pGrandParent->pLeft == pParent && pParent->pRight == pNode)
	{
		// LR
		pNode->type = ReverseColor(pNode->type);
		pGrandParent->type = ReverseColor(pGrandParent->type);
		RotateRR(pParent);
		pNode = (RedBlackTreeNode<T>*)RotateLL(pGrandParent);
	}
	else if (pGrandParent->pRight == pParent && pParent->pLeft == pNode)
	{
		// RL
		pNode->type = ReverseColor(pNode->type);
		pGrandParent->type = ReverseColor(pGrandParent->type);
		RotateLL(pParent);
		pNode = (RedBlackTreeNode<T>*)RotateRR(pGrandParent);
	}
	else
	{
		// RR
		pParent->type = ReverseColor(pParent->type);
		pGrandParent->type = ReverseColor(pGrandParent->type);
		pNode = (RedBlackTreeNode<T>*)RotateRR(pGrandParent);
	}
	if (pGrandParent == pRoot) pRoot = pNode;
}

template<typename T>
void RedBlackBST<T>::SolveRemovalImbalance(RedBlackTreeNode<T>* pNode)
{
}

template<typename T>
inline RedBlackType RedBlackBST<T>::GetColor(RedBlackTreeNode<T>* pNode) const
{
	return (pNode == nullptr) ? BLACK : pNode->type;
}

template<typename T>
inline RedBlackType RedBlackBST<T>::ReverseColor(RedBlackType type) const
{
	RedBlackType ret;
	switch (type)
	{
	case RED:
		ret = BLACK;
		break;
	case BLACK:
		ret = RED;
		break;
	}
	return ret;
}
