#include <iostream>
using namespace std;

int main()
{
	char c = 'c';
	cout<<"sizeof(c): "<<sizeof(c)<<endl; 
	wchar_t wc = 'w';
	cout<<"sizeof(wc): "<<sizeof(wc)<<endl; 
	string s = "";
	s += wc;
//	s += c;
	
	cout<<"sizeof(c): "<<sizeof(s[0])<<endl; 
//	cout<<"sizeof(c): "<<sizeof(s[1])<<endl; 
	return 0;
}
