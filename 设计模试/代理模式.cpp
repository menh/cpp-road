//代理模式

#include <iostream>
using namespace std;

class Subject{
	public:
		virtual void action() = 0;
};

class RealSubject: public Subject{
	public:
		void action(){
			cout<<"I am real subject"<<endl; 
		}
};

class ProxySubject: public Subject{
	public:
		ProxySubject(){
			subject = new RealSubject();
		}
		void action(){
			subject->action();
		}
	
	private:
		Subject* subject;
};
int main()
{
	Subject* subject = new ProxySubject();
	subject->action();
	return 0;
 } 
