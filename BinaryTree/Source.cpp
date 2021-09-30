#include "BiTree.h"

int main()
{
	BiTree<float> a;
	a.AddElement(4);
	a.AddElement(3);
	a.AddElement(2);
	a.AddElement(6);
	a.AddElement(5);
	float b = a.MinElement();
	a.DeleteElement(3);
	return 0;

}