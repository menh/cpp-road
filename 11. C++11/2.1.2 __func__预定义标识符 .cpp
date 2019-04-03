#include <iostream>
using namespace std;

const char* testFunc(){
	return __func__;
}

struct TestStruct{
	TestStruct() : name(__func__){
	}
	const char* name;
};

class TestClass{
	public:
		TestClass() : name(__func__){}
		const char* name;
};
int main()
{
	cout<<testFunc()<<endl;
	TestStruct ts;
	cout<<ts.name<<endl;
	TestClass tc;
	cout<<tc.name<<endl;
	return 0;
} 
