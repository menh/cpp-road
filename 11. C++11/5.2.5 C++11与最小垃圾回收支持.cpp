#include <iostream>
#include <memory>
using namespace std;
int main()
{
	int *p = new int;
	//declare_reachable(p);
	declare_no_pointers(p,12);
	//int* q = (int*) ((long long) p ^ 2012);
	
	//q = undeclare_reachable<int>((int*) ((long long) q ^ 2012));
	
	//*q = 10;
	return 0;
 } 
