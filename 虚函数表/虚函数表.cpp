#include <iostream>
using namespace std;

class Base{
	virtual void f() { cout << "Base::f" << endl; }

	virtual void g() { cout << "Base::g" << endl; }

	virtual void h() { cout << "Base::h" << endl; }

}; 
int main()
{
	typedef void(*Fun)(void);
	Base b;
	Fun pFun = NULL;
	
	cout << "虚函数表地址：" << (int*)(&b) << endl;

	cout << "虚函数表 — 第一个函数地址：" << (int*)*(int*)(&b) << endl;
	cout << "虚函数表 — 第二个函数地址：" << (int*)*(int*)(&b) + 1<< endl;
	cout << "虚函数表 — 第二个函数地址：" << (int*)*(int*)(&b) + sizeof(int*)/sizeof(int)<< endl;


	int* funcP =  (int*)*(int*)(&b) + sizeof(int*)/sizeof(int);
	pFun = (Fun)*(funcP);
    //pFun = (Fun)*((int*)*(int*)(&b) + 1);  // Base::g()
	pFun();

	return 0;
}
