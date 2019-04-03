#include <iostream>
using namespace std;
template <typename T, typename U> 
void bit_copy(T& a, U& b)
{
	static_assert(sizeof(b) == sizeof(a), "the parameters of bit_copy must have same width.");
	
} 

int positive(const int n){
	static_assert(1 > 0, "value must > 0");
}
int main()
{
	int a = 0x2468;
	double b;
	bit_copy(a,b);
	return 0;
}
