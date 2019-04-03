#include <iostream>
using namespace std;
class Base{
	virtual void func1();
	virtual void func2();
};

class DerivedMid: public Base{
	virtual void func1() override;
	virtual void func2() override final;
};

class DerivedTop: public DerivedMid{
	virtual void func1() override;
	//virtual void func2() override final;
};
int main()
{
	
	return 0;
} 
