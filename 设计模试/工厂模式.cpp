//工厂模式
#include <iostream>
using namespace std;

class Fruit{
	public:
		virtual void fruitInfo() = 0;
};

class Apple: public Fruit{
	void fruitInfo(){
		cout<< "this is apple"<<endl; 
	} 
};

class Orange: public Fruit{
	void fruitInfo(){
		cout<< "this is orange"<<endl; 
	} 
};

class Banana: public Fruit{
	void fruitInfo(){
		cout<< "this is banana"<<endl; 
	} 
};



class Factory{
	public:
		Fruit* getFruit(string name)
		{
			if(name == "Apple"){
				return new Apple();
			}
			else if(name == "Orange"){
				return new Orange();
			}
			else if(name == "Banana"){
				return new Banana();
			}
		}
};

int main()
{
	Factory* factory = new Factory();
	Fruit* apple =  factory->getFruit("Apple");
	apple->fruitInfo(); 
	return 0;
 } 
