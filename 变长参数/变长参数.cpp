//https://www.cnblogs.com/qicosmos/p/4325949.html
#include <iostream>

using namespace std;

#include <stdarg.h>
int sum(int count, ...) {  //格式:count代表参数个数, ...代表n个参数
 
	va_list ap;  //声明一个va_list变量
	va_start(ap, count);  //第二个参数表示形参的个数
 
	int sum = 0;
	for (int i = 0; i < count; i++) {
		sum += va_arg(ap, int);   //第二个参数表示形参类型
	}
	
	va_end(ap);  //用于清理
 
	return sum;
}

template <class... T>
void f(T... args)
{    
	va_list ap;
    cout << sizeof...(args) << endl; //打印变参的个数
}


int main()
{
	
	f(1,2,3,4.5);
	return 0;
 } 
