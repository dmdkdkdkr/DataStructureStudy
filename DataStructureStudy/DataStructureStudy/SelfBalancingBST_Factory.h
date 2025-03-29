#pragma once
#include "SelfBalancingBST.h"
#include "AVLBinarySearchTree.h"
#include "RedBlackBST.h"

enum SelfBalancingTreeType
{
	AVL,
	RED_BLACK
};

template<typename T>
class SelfBanlancingBST_Factory
{
public:
	static SelfBalancingBST<T>* Create(SelfBalancingTreeType _type);
};

template<typename T>
SelfBalancingBST<T>* SelfBanlancingBST_Factory<T>::Create(SelfBalancingTreeType _type)
{
	SelfBalancingBST<T>* pTree = nullptr;

	switch (_type)
	{
	case AVL:
		pTree = new AVLBinarySearchTree<T>();
		break;
	case RED_BLACK:
		pTree = new RedBlackBST<T>();
		break;
	}

	return pTree;
}
