#include <iostream>
using namespace std;

class Init{
	public:
		int a = 1;
		double b {1.2};
		const static int e = 1.4;
};
int main()
{
	Init init;
	cout<<init.b<<endl;
	return 0;
} 
