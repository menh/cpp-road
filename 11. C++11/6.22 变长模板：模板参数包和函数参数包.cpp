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

template <typename... Elements> class tuple1; //变长模板声明

template <typename Head, typename... Tail> //递归的偏特化定义 
class tuple1<Head, Tail...> : private tuple1<Tail...>{
	Head head;
};

template<> class tuple1<>{}; //边界条件 

template <long... nums> struct Multiply;

template <long first, long ...last>
struct Multiply<first, last...>{
	static const long val = first * Multiply<last...>::val;
};
template<>
struct Multiply<>{
	static const long val = 1;
};

int main()
{
	tuple1<double, int, char, float> t1;// tuple<double, (int, char, float)> 
	cout<< Multiply<2, 3, 4, 5>::val<<endl;
	return 0;
}
