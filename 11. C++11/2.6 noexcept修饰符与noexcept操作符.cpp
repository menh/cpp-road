#include <iostream>
using namespace std;
struct A{
	~A(){
		throw;
	}
};

struct B{
	~B() noexcept(false){
		throw 2;
	}
};
int main()
{
	try{
		B b;
	}
	catch(...){
		cout<<"b throw"<<endl;
	}

	try{
		A a;
	}
	catch(...){
		cout<<"a throw"<<endl;
	}
	return 0;
}
