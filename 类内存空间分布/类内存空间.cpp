#include <iostream>
using namespace std;

class A
{
	public:
		virtual int virtualFunc1() = 0;
		virtual int virtualFunc2() = 0;
};

class A1
{
	private:
		int a;
	public:
		virtual int function1() = 0;
		virtual int function2() = 0;
};
class B : private  A ,public A1
{
	
};
int main()
{
	cout<<sizeof(A)<<endl;
	cout<<sizeof(B)<<endl;
	return 0;
 } 
