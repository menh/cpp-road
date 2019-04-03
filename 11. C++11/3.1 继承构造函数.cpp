#include <iostream>
using namespace std;

struct A{
	A(int _a) { a = _a;}
	int a;
};

struct B : A {
	using A::A;

};
int main()
{
	B b(1);
	
	cout<<b.a<<endl;
	return 0;
} 
