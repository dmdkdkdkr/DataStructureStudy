#pragma once
#include "LinkedQueue.h"

template <typename T>
class SelfBalancingTreeNode
{
public:
	T data;
};

template<typename T>
class SelfBalancingBST
{
protected:
	int count;

public:
	SelfBalancingBST();
	virtual ~SelfBalancingBST() {}

	virtual bool Insert(T data) = 0;
	virtual bool Remove(T data) = 0;
	virtual void Clear() = 0;
	virtual SelfBalancingTreeNode<T>* Search(T data) const = 0;
	virtual void Display() const = 0;

	int Count() const;
	bool IsEmpty() const;

protected:
	virtual SelfBalancingTreeNode<T>* RotateLL(SelfBalancingTreeNode<T>* pNode) = 0;
	virtual SelfBalancingTreeNode<T>* RotateRR(SelfBalancingTreeNode<T>* pNode) = 0;
};

template<typename T>
SelfBalancingBST<T>::SelfBalancingBST() : count(0) {}

template<typename T>
inline int SelfBalancingBST<T>::Count() const { return count; }

template<typename T>
inline bool SelfBalancingBST<T>::IsEmpty() const { return count == 0; }