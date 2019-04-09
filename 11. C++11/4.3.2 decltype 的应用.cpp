#include <iostream>
#include <typeinfo>
#include <vector>
using namespace std;

int main()
{
	//基本数据类型推导重命名 
	using size_t = decltype(sizeof(0));
	using ptrdiff_t = decltype((int*)0 - (int*)0);
	using nullptr_t = decltype(nullptr);
	
	vector<int> vec;
	typedef decltype(vec.begin()) vectype; 
	return 0;
 } 
