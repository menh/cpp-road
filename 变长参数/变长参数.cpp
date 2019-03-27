//https://www.cnblogs.com/qicosmos/p/4325949.html
#include <iostream>

using namespace std;

#include <stdarg.h>
int sum(int count, ...) {  //��ʽ:count�����������, ...����n������
 
	va_list ap;  //����һ��va_list����
	va_start(ap, count);  //�ڶ���������ʾ�βεĸ���
 
	int sum = 0;
	for (int i = 0; i < count; i++) {
		sum += va_arg(ap, int);   //�ڶ���������ʾ�β�����
	}
	
	va_end(ap);  //��������
 
	return sum;
}

template <class... T>
void f(T... args)
{    
	va_list ap;
    cout << sizeof...(args) << endl; //��ӡ��εĸ���
}


int main()
{
	
	f(1,2,3,4.5);
	return 0;
 } 
