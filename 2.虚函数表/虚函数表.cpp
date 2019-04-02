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
	cout<<"ʵ��c�ĵ�ַ:"<<&c<<endl; //�൱��ͼ��Aʵ���ڴ���׵�ַ 
	cout<<endl;
	cout<<"ʵ��c���׵�ַ�����ݻ�̳���Base1�麯����ĵ�ַ"<<(int*)*(int*)(&c)<<endl;
	cout<<"ʵ��c���׵�ַ�����ݻ�̳���Base2�麯����ĵ�ַ"<<(int*)*((int*)(&c) + 2)<<endl;
	cout<<endl;
	
	typedef void(*Fun)(void); //����һ������ָ��
	Fun pFun = NULL;
	int* pf = (int*)*(int*)(&c); //ָ���麯����ĵ�һ��ָ��
	int* pg = (int*)*(int*)(&c) + sizeof(int*)/sizeof(int);
	int* ph = (int*)*(int*)(&c) + sizeof(int*)/sizeof(int) + sizeof(int*)/sizeof(int);
	int* pi = (int*)*(int*)(&c) + sizeof(int*)/sizeof(int) + sizeof(int*)/sizeof(int) + sizeof(int*)/sizeof(int);
	cout << "Base1�麯���� �� ��һ��������ַ��" << pf << endl;
	cout << "Base1�麯���� �� �ڶ���������ַ��" << pg << endl;
	cout << "Base1�麯���� �� ������������ַ��" << ph<< endl;
	cout << "Base1�麯���� �� ���ĸ�������ַ��" << pi << endl;	
	pFun = (Fun)* pf;
	pFun();
	pFun = (Fun)* pg;
	pFun();
	pFun = (Fun)* ph;
	pFun();
	pFun = (Fun)* pi;
	pFun();
	pf = (int*)*((int*)(&c) + 2); //ָ���麯����ĵ�һ��ָ��
	pg = (int*)*((int*)(&c) + 2) + sizeof(int*)/sizeof(int);
	ph = (int*)*((int*)(&c) + 2) + sizeof(int*)/sizeof(int) + sizeof(int*)/sizeof(int);
	cout << "Base2�麯���� �� ��һ��������ַ��" << pf << endl;
	cout << "Base2�麯���� �� �ڶ���������ַ��" << pg << endl;
	cout << "Base2�麯���� �� ������������ַ��" << ph<< endl;
	pFun = (Fun)* pf;
	pFun();
	pFun = (Fun)* pg;
	pFun();
	pFun = (Fun)* ph;
	pFun();
	return 0;
}
