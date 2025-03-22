#pragma once

template <typename T>
class LinkedBinaryTreeNode
{
public:
	T data;
	LinkedBinaryTreeNode<T>* pLeft;
	LinkedBinaryTreeNode<T>* pRight;

	LinkedBinaryTreeNode(T _data);
};

template<typename T>
LinkedBinaryTreeNode<T>::LinkedBinaryTreeNode(T _data) : data(_data), pLeft(NULL), pRight(NULL) {}