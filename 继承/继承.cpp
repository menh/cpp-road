#include <iostream>
using namespace std;

class Parent{
	public:
		virtual void publicParentFunc();
	protected:
		void protectedParentFunc();
	private:
		void privateParentFunc();

}; 

class Parent2{
	public:
		virtual void publicParentFunc();
	protected:
		void protectedParentFunc();
	private:
		void privateParentFunc();

}; 


class Child : public Parent, public Parent2{
	public:
		virtual void publicParentFunc();
	
};
/*
class{
	public:
		void publicParentFunc();
	protected:
		void protectedParentFunc();
	private://²»¿É¼û 
		void privateParentFunc();	
};*/
int main()
{
	cout<<sizeof(Parent)<<endl;
	cout<<sizeof(Child)<<endl;
	return 0;
}
