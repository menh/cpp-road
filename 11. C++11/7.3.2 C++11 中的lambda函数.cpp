#include <iostream>
using namespace std;
int main()
{
	[]{};
	int a = 3;
	int b = 4;
	[=] { return a + b; };
	auto fun1 = [&](int c) { b = a + c; };
	auto fun2 = [=, &b](int c) -> int { return b+= a + c ;};
	return 0;
 } 
