#include <iostream>
using namespace std;

class Info{
	public:
		Info(){
			a = 0;
		}
		Info(int i){ 
			new (this) Info();
			b = 1;
		}
		Info(char c) : Info(){
		
			c = 'c';
		}
		int a;
		int b;
		char c;
};

int main()
{
	Info(1);
	return 0;
} 
