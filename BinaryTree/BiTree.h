#pragma once
#ifndef BITREE_H_
#define BITREE_H_
#include <iostream>

template <typename Type>
class BiTree
{
	struct NodeTree
	{
		Type element;
		NodeTree* left;
		NodeTree* right;

	};
private:
	NodeTree* root;
	int countOfElement = 0;
	void AddElement(NodeTree** node, Type elem);
	void DeleteTree(NodeTree* node);
	bool DeleteElement(NodeTree** node, Type elem);
	NodeTree* SearchElement(const Type& elem, NodeTree** currNode, NodeTree& parent)
	{
		NodeTree* node = *currNode;
		if (elem == node->element)
			return node;
		else if (elem < node->element)
		{
			if (node->left == nullptr) return nullptr;
			parent = *node;
			node = node->left;
			SearchElement(elem, &node, parent);
		}
		else
		{
			if (node->right == nullptr) return nullptr;
			parent = *node;
			node = node->right;
			SearchElement(elem, &node, parent);
		}
	};
public:
	BiTree() { root = nullptr; };
	~BiTree() { DeleteTree(root); };
	Type& MaxElement();
	Type& MinElement();
	void AddElement(Type elem);
	bool DeleteElement(Type elem);


};



template<typename Type>
inline void BiTree<Type>::AddElement(NodeTree** node, Type elem)
{
	if (*node == nullptr)
	{
		NodeTree* temp = new NodeTree;
		temp->element = elem;
		temp->left = nullptr;
		temp->right = nullptr;
		*node = temp;
		countOfElement++;
	}
	else if (elem < (*node)->element)
	{
		AddElement(&(*node)->left, elem);
	}
	else
	{
		AddElement(&(*node)->right, elem);
	}
}

template<typename Type>
inline void BiTree<Type>::DeleteTree(NodeTree* node)
{
	if (node != nullptr)
	{
		DeleteTree(node->left);
		DeleteTree(node->right);
		delete node;
	}
	countOfElement = 0;
}

template<typename Type>
inline bool BiTree<Type>::DeleteElement(NodeTree** node, Type elem)
{
	NodeTree* parent = new NodeTree;
	NodeTree* currNode = SearchElement(elem, node, *parent);

	if (currNode)
	{
		if (currNode->left == nullptr && currNode->right == nullptr)
		{
			parent->left = nullptr;
			parent->right = nullptr;
			delete currNode;
		}
		else if (currNode->left != nullptr && currNode->right == nullptr)
		{
			currNode = currNode->left;
		}
		countOfElement--;
		delete parent;
		return true;
	}
	else return false;
}



template<typename Type>
inline bool BiTree<Type>::DeleteElement(Type elem)
{
	if (DeleteElement(&root, elem))
		return true;
	else return false;
}



template<typename Type>
inline Type& BiTree<Type>::MaxElement()
{
	NodeTree* node = root;
	if (node != nullptr)
	{
		while (node->right != nullptr)
		{
			node = node->right;
		}
		return node->element;
	}

}

template<typename Type>
inline Type& BiTree<Type>::MinElement()
{
	NodeTree* node = root;
	if (node != nullptr)
	{
		while (node->left != nullptr)
		{
			node = node->left;
		}
		return node->element;
	}

}

template<typename Type>
inline void BiTree<Type>::AddElement(Type elem)
{
	AddElement(&root, elem);
}



#endif // !BITREE_H_
