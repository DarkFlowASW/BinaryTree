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
		NodeTree* parent;
		unsigned int key = 0;

	};
private:
	NodeTree* root;
	int countOfElement = 0;
	void AddElement(NodeTree** node, Type elem);
	void DeleteTree(NodeTree* node);
	bool DeleteElement(NodeTree* node);
	NodeTree* CreatNode(Type elem, NodeTree* currParent)
	{
		NodeTree* node = new NodeTree;
		node->left = node->right = nullptr;
		node->element = elem;
		node->parent = currParent;
		return node;
	}
	NodeTree* SearchElement(const Type& elem, NodeTree** currNode)
	{
		NodeTree* node = *currNode;
		if (elem == node->element)
			return node;
		else if (elem < node->element)
		{
			if (node->left == nullptr) return nullptr;
			node = node->left;
			SearchElement(elem, &node);
		}
		else
		{
			if (node->right == nullptr) return nullptr;
			node = node->right;
			SearchElement(elem, &node);
		}
	};
	NodeTree* SearchElementByKey(const unsigned int k, NodeTree** currNode)
	{
		NodeTree* node = *currNode;
		if (k == node->key)
			return node;
		else if (k < node->key)
		{
			if (node->left == nullptr) return nullptr;
			node = node->left;
			SearchElementByKey(k, &node);
		}
		else
		{
			if (node->right == nullptr) return nullptr;
			node = node->right;
			SearchElementByKey(k, &node);
		}
	};
	NodeTree* FindMaxLocal(NodeTree* node)
	{
		while (node->right)
		{
			node = node->right;
		}
		return node;
	}
	static void PrintTree(std::ostream& os, const NodeTree* node)
	{
		if (node != nullptr)
		{
			PrintTree(os, node->left);
			os << node->element << ",";
			PrintTree(os, node->right);
		}
	}
public:
	BiTree() { root = nullptr; };
	~BiTree() { DeleteTree(root); };
	Type& MaxElement();
	Type& MinElement();
	int SearchElement(Type& elem);
	Type& SearchElementByKey(unsigned int k);
	void AddElement(Type elem);
	bool DeleteElement(Type elem);
	void Numbering(NodeTree*& node, unsigned int numberKey = 0);
	void Numbering();





	friend std::ostream& operator<<(std::ostream& os, const BiTree& tree)
	{
		PrintTree(os, tree.root);
		return os;

	}

};



template<typename Type>
inline void BiTree<Type>::AddElement(NodeTree** node, Type elem)
{
	if (*node == nullptr)
	{
		*node = CreatNode(elem, nullptr);
		countOfElement++;
		return;
	}
	NodeTree* currNode = root;
	while (currNode)
	{
		if (elem >= currNode->element)
			if (currNode->right)
			{
				currNode = currNode->right;
				continue;
			}
			else
			{
				currNode->right = CreatNode(elem, currNode);
				countOfElement++;
				return;
			}
		else if (elem < currNode->element)
		{
			if (currNode->left)
			{
				currNode = currNode->left;
				continue;
			}
			else
			{
				currNode->left = CreatNode(elem, currNode);
				countOfElement++;
				return;
			}
		}
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
		node = nullptr;
	}
	countOfElement = 0;
}

template<typename Type>
inline bool BiTree<Type>::DeleteElement(NodeTree* node)
{
	if (node->left && node->right)
	{
		NodeTree* localMax = FindMaxLocal(node->left);
		node->element = localMax->element;
		DeleteElement(localMax);
		return true;
	}
	else if (node->left)
	{
		if (node == node->parent->left)
			node->parent->left = node->left;
		else
			node->parent->right = node->left;
	}
	else if (node->right)
	{
		if (node == node->parent->right)
			node->parent->right = node->right;
		else
			node->parent->left = node->right;
	}
	else
	{
		if (node == node->parent->left)
			node->parent->left = nullptr;
		else
			node->parent->right = nullptr;
	}
	countOfElement--;
	delete node;
}


template<typename Type>
inline bool BiTree<Type>::DeleteElement(Type elem)
{
	NodeTree* nodeDelet = SearchElement(elem, &root);
	if (DeleteElement(nodeDelet))
		return true;
	else return false;
}

template<typename Type>
void  BiTree<Type>::Numbering()
{
	NodeTree* node = root;
	Numbering(node);
}
template<typename Type>
inline void BiTree<Type>::Numbering(NodeTree*& node, unsigned int numberKey)
{
	static unsigned int  num;
	num = numberKey;
	if (node != nullptr)
	{
		Numbering(node->left, num);
		node->key = ++num;
		Numbering(node->right, num);
	};
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
int BiTree<Type>::SearchElement(Type& elem)
{
	NodeTree* node = SearchElement(elem, &root); // Ñalls an inner private function
	return node->key;
}
template<typename Type>
Type& BiTree<Type>::SearchElementByKey(unsigned int k)
{
	NodeTree* node = SearchElementByKey(k, &root); // Ñalls an inner private function

	return  node->element;
}

template<typename Type>
inline void BiTree<Type>::AddElement(Type elem)
{
	AddElement(&root, elem); // Ñalls an inner private function
}




#endif // !BITREE_H_
