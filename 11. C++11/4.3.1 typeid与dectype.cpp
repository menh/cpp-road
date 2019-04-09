#include <iostream>
#include <typeinfo>
using namespace std;
class White{	
};

class Black{	
};
int main()
{
	White a;
	decltype(a) b;
	cout<< typeid(a).name() << endl;
	cout<< typeid(b).name() << endl;
	return 0;
 } 
