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
	bool d = a.DeleteElement(2);
	return 0;

}