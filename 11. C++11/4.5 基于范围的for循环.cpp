#include <iostream>
#include <typeinfo>
#include <vector>
#include <algorithm>
using namespace std;
int action1(int& e)
{
	e *= 2;
	return e;
}
int action2(int & e)
{
	cout<< e <<endl;
}
int main()
{
	int arr[5] = {1,2,3,4,5};
	for_each(arr, arr + sizeof(arr) / sizeof(arr[0]), action1);
	for_each(arr, arr + sizeof(arr) / sizeof(arr[0]), action2);
	for(auto e : arr)
	{
		action2(e);
	}
	return 0;
 } 
