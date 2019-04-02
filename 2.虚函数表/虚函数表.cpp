#include <iostream>
using namespace std;

class Base1{
	public:
		virtual void f() { cout << "Base1::f" << endl; }
		virtual void g() { cout << "Base1::g" << endl; }
		virtual void h() { cout << "Base1::h" << endl; }
}; 

class Base2{
	public:
		virtual void f() { cout << "Base2::f" << endl; }
		virtual void g() { cout << "Base2::g" << endl; }
		virtual void h() { cout << "Base2::h" << endl; }
}; 
class Child: public Base1,Base2{
	virtual void i() { cout << "Child::i" << endl; }
}; 
int main()
{
	Child c;
	cout<<"sizeof c:"<<sizeof(c)<<endl;
	cout<<"实例c的地址:"<<&c<<endl; //相当于图中A实例内存的首地址 
	cout<<endl;
	cout<<"实例c的首地址的内容或继承自Base1虚函数表的地址"<<(int*)*(int*)(&c)<<endl;
	cout<<"实例c的首地址的内容或继承自Base2虚函数表的地址"<<(int*)*((int*)(&c) + 2)<<endl;
	cout<<endl;
	
	typedef void(*Fun)(void); //声明一个函数指针
	Fun pFun = NULL;
	int* pf = (int*)*(int*)(&c); //指向虚函数表的第一个指针
	int* pg = (int*)*(int*)(&c) + sizeof(int*)/sizeof(int);
	int* ph = (int*)*(int*)(&c) + sizeof(int*)/sizeof(int) + sizeof(int*)/sizeof(int);
	int* pi = (int*)*(int*)(&c) + sizeof(int*)/sizeof(int) + sizeof(int*)/sizeof(int) + sizeof(int*)/sizeof(int);
	cout << "Base1虚函数表 — 第一个函数地址：" << pf << endl;
	cout << "Base1虚函数表 — 第二个函数地址：" << pg << endl;
	cout << "Base1虚函数表 — 第三个函数地址：" << ph<< endl;
	cout << "Base1虚函数表 — 第四个函数地址：" << pi << endl;	
	pFun = (Fun)* pf;
	pFun();
	pFun = (Fun)* pg;
	pFun();
	pFun = (Fun)* ph;
	pFun();
	pFun = (Fun)* pi;
	pFun();
	pf = (int*)*((int*)(&c) + 2); //指向虚函数表的第一个指针
	pg = (int*)*((int*)(&c) + 2) + sizeof(int*)/sizeof(int);
	ph = (int*)*((int*)(&c) + 2) + sizeof(int*)/sizeof(int) + sizeof(int*)/sizeof(int);
	cout << "Base2虚函数表 — 第一个函数地址：" << pf << endl;
	cout << "Base2虚函数表 — 第二个函数地址：" << pg << endl;
	cout << "Base2虚函数表 — 第三个函数地址：" << ph<< endl;
	pFun = (Fun)* pf;
	pFun();
	pFun = (Fun)* pg;
	pFun();
	pFun = (Fun)* ph;
	pFun();
	return 0;
}
