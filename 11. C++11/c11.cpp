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
	cout<<"Standard Clib: " << __STDC_HOSTED__<<endl;
	cout<<"Standard C: " << __STDC__<<endl;
	
//	cout<<"C Standard version: " << __STDS_VERSION__ <<endl;
//	cout<<"ISO/IEC " <<__STDC_ISO_10646__<<endl; 
	return 0;
} 
