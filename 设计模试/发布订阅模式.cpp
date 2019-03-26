#include <iostream>
#include <vector>
#include <list>
using namespace std;
class Subject;
class Observer{
	public:
		Observer()
		{
			state = "³õÊ¼";
		}
		
		virtual ~Observer()
		{
			
		}
		virtual void update(Subject* subject) = 0;
		virtual void setState(string& str){
			this->state = str;
		}
		virtual string getState(){
			return this->state;
		}
		virtual void printInfo() = 0;
		
	private:
		string state;
};

class Subject{
	public:
		Subject()
		{
			observers = new list<Observer*>();
		}
		
		~Subject()
		{
			
		}
		
		void attach(Observer* obs)
		{
			if(obs != NULL)
			{
				observers->push_back(obs);
			}
		}
		
		void detach(Observer* obs)
		{
			if(obs != NULL)
			{
				observers->remove(obs);
			}
		}
		
		void notify()
		{
			list<Observer*>::iterator iter;
			for(iter = observers->begin(); iter!= observers->end(); ++iter)
			{
				(*iter)->update(this);
			}
		}
		
		void setState(const string& str)
		{
			this->state = str;
		}
		
		string getState()
		{
			return this->state;
		}
	private:
		list<Observer*>* observers;
		string state;
}; 





class ConcreteObserverA: public Observer{
	public:
		ConcreteObserverA(){
			
		}
		~ConcreteObserverA(){
			
		}
		virtual void update(Subject* subject){
			string str = subject->getState();
			this->setState(str);
		}
		void printInfo(){
			cout<<"ConcreteObserverA change to " + this->getState() <<endl;
		}
};

class ConcreteObserverB: public Observer{
	public:
		ConcreteObserverB(){
			
		}
		~ConcreteObserverB(){
			
		}
		virtual void update(Subject* subject){
			string str = subject->getState();
			this->setState(str);
		}
		void printInfo(){
			cout<<"ConcreteObserverB change to " + this->getState() <<endl;
		}
};

int main()
{
	Subject* subject = new Subject();
	Observer* observerA = new ConcreteObserverA();
	Observer* observerB = new ConcreteObserverB();
	
	subject->attach(observerA);
	subject->attach(observerB);
	
	subject->setState("·¢²¼¶©ÔÄ");
	
	observerA->printInfo();
	observerB->printInfo();
	
	subject->notify();
	observerA->printInfo();
	observerB->printInfo();
	return 0;
}
