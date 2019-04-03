#include <iostream>
using namespace std;

template<class T, class U = int>
void add(T t, U u){	
	cout<< t + u <<endl;
}
int main()
{
	add(1,2);
	string t = "1";
	string u = "2";
	add(t,u);
	return 0;
} 
