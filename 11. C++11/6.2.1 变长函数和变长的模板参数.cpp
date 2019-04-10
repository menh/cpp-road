#include <iostream>
#include <stdarg.h>
using namespace std;
double SumOfFloat(int count, ...)
{
	va_list ap;
	double sum  = 0;
	va_start(ap, count);
	for(int i = 0; i < count; i++)
	{
		sum += va_arg(ap, double);
	}
	va_end(ap);
	return sum;
}
int main()
{
	cout<< SumOfFloat(2, 1.0, 2.2) <<endl;
	return 0;
}
