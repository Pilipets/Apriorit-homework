#include "MyVector.h"
#include<vector>
using MineSTL::MyVector;
using std::cout;
using std::endl;
int main()
{
	MyVector<int> a;
	for (int i = 0; i < 10; ++i)
		a.push_back(i);

	std::cout << a << std::endl;
	MyVector<int> b(a);
	std::cout << b << std::endl;
	std::cout << a << std::endl;
	cout << endl;

	a.push_back(-21);
	MyVector<int> c(std::move(a));
	std::cout << c << std::endl;
	std::cout << b << std::endl;
	std::cout << a << std::endl;
	cout << endl;

	MyVector<int> d;
	d = b;
	d.push_back(13);
	cout << d << endl;
	MyVector<int> f;
	f = std::move(d);
	cout << d << endl;
	cout << f << endl;

	d = a;
	cout << d << endl;
	d.push_back(-34534);
	d = std::move(b);
	cout << b << endl;
	cout << d << endl;
	system("pause");
	return 0;
}