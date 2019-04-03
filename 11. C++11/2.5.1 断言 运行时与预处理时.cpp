#include <iostream>
#include <cassert>
using namespace std;
#define NDEBUG NDEBUG

#ifdef NDEBUG
# define assert(expr) (static_cast<void>(0))
#endif 

char* ArrayAlloc(int n){
	assert(n > 0);
	return new char[n];
}
int main()
{
	char* a = ArrayAlloc(0);
	return 0;
}
