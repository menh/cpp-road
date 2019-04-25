#include <iostream>
using namespace std;
struct alignas(2) HowManyBytes{
	char a;
	int b;
};

struct alignas(32) ColorVector{
	double a;
	double b;
	double c;
	double d;
};
int main()
{
	cout<< "sizeof(char): " << sizeof(char) <<endl;
	cout<< "sizeof(int): " << sizeof(int) <<endl;
	cout<< "sizeof(HowManyBytes): " << sizeof(HowManyBytes) <<endl;
	
	cout<<endl;
	cout<< "offset of char a: " << offsetof(HowManyBytes, a) <<endl;
	cout<< "offset of int b: " << offsetof(HowManyBytes, b) <<endl;
	
	cout<< "alignof(ColorVector): " << alignof(ColorVector) <<endl;
	
	cout<< alignof(int)<<endl;
	return 0;
 } 
