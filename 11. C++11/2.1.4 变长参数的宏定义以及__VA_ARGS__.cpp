#include <iostream>
using namespace std;
// stderr 标准错误输出设备 
#define LOG(...){\
	fprintf(stderr,"%s: Line %d:\n", __FILE__, __LINE__);\
	fprintf(stderr, __VA_ARGS__);\
	fprintf(stderr, "\n");\
}

int main()
{
	int x = 3;
	LOG("x = %d", x); // fprintf(stderr,"x = %d", x);
	return 0;
} 
