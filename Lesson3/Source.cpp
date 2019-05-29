#include"MyVector2.h"

void method(MyVector<int> tmp)
{

	int a = 3;
	tmp.push_back(-1, "-1");
}
int main()
{
	MyVector<int> a;
	a.push_back(1, "1");
	a.push_back(3, "3");
	a.push_back(2, "2");
	a.push_back(5, "5");
	MyVector<int> b;
	b.push_back(6, "6");
	MyVector<int> c(b);
	b.push_back(7, "7");
	c.push_back(9, "9");
	MyVector<int> d = a;
	a.push_back(-1, "-1");
	MyVector<int> a1;
	a1.push_back(5, "5");
	//a1 = MyVector<int>();
	//std::vector<int> c1 = a;
	//MyVector<int> tmp(MyVector<int>(c1));
	//system("pause");
	return 0;
}