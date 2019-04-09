#include <iostream>
#include <typeinfo>
#include <vector>
using namespace std;
template<typename T1, typename T2>
auto add(const T1& t1, const T2& t2) -> decltype(t1 + t2)
{
	return t1 + t2;
} 

double add(const double& d1, const double& d2)
{
	return d1 + d2;
}

int add (const int& i1, const int& i2)
{
	return i1 + i2;
}

template<typename T>
auto Forward(const T& t1, const T& t2) -> decltype(add(t1, t2))
{
	return add(t1, t2);
} 
int main()
{
	cout<< add(1,2) <<endl;
	cout<< add(1.2,2.3) <<endl;
	cout<<Forward(1,2)<<endl;
	cout<<Forward(1.2,2.3)<<endl;
	return 0;
 } 
