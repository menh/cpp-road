#include <iostream>
#include <typeinfo>
#include <vector>
using namespace std;
void add(){
	
}
int main()
{
	decltype(add) a;

	cout<< typeid(a).name() <<endl;
	
	
	return 0;
 } 
