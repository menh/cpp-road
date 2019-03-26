// virtualFunction.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;
class Base {
	virtual void funA() {
		cout << "funcA" << endl;
	}

	virtual void funB() {
		cout << "funcB" << endl;
	}

	virtual void funC() {
		cout << "funC" << endl;
	}
};
typedef void(*Fun)(void);
int main()
{
	Base b;
	Fun pFun = NULL;

	cout << "虚函数表地址：" << (int*)(&b) << endl;

	cout << "虚函数表 — 第一个函数地址：" << (int*)*(int*)(&b) << endl;
	cout << "虚函数表 — 第二个函数地址：" << (int*)*(int*)(&b) + 1 << endl;
	cout << "虚函数表 — 第二个函数地址：" << (int*)*(int*)(&b) + sizeof(int*) / sizeof(int) << endl;


	int* funcP = (int*)*(int*)(&b) + sizeof(int*) / sizeof(int);
	pFun = (Fun)*(funcP);
	//pFun = (Fun)*((int*)*(int*)(&b) + 1);  // Base::g()
	pFun();
    return 0;
}

