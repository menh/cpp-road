#include <iostream>
using namespace std;
int& referenceFun(int& num)
{
	cout<<"referenceFun: " << (int*)&num <<endl;
	return num;
}

int valueFun(int& num)
{
	cout<<"valueFun: " << (int*)&num <<endl;
	return num;
} 
int main()
{
	int num  = 0;
	cout<<"num: " << (int*)&num <<endl;
	int& referenceFunNum = referenceFun(num);
	cout<<"referenceFunNum: " << (int*)&referenceFunNum <<endl;
	int valueFunNum = valueFun(num);
	cout<<"valueFunNum: " << (int*)&valueFunNum <<endl;
	return 0;
}
