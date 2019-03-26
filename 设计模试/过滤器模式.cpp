#include <iostream>
#include <vector>
using namespace std;

class Person{
	private:
		string name;
		int age;
		string sex;
	public:
		Person(string name, int age, string sex)
		{
			this->name = name;
			this->age = age;
			this->sex = sex;
		}
		string getName(){
			return this->name;
		}
		int getAge(){
			return this->age;
		}
		string getSex(){
			return this->sex;
		}
};

class Filter{
	public:
		virtual vector<Person> filter(vector<Person> persons) = 0; 
};

class NameFilter: public Filter{
	public:
		NameFilter(string filterName)
		{
			this->filterName = filterName;
		}
		
		vector<Person> filter(vector<Person> persons)
		{
			vector<Person> filterPerson;
			for(int persons_i = 0; persons_i < persons.size(); ++persons_i)
			{
				if(persons[persons_i].getName() == this->filterName){
					filterPerson.push_back(persons[persons_i]);
				}
			}
			return filterPerson;
		}
		
	private:
		string filterName;
}; 

class AgeFilter: public Filter{
	public:
		AgeFilter(int filterAge)
		{
			this->filterAge = filterAge;
		}
		
		vector<Person> filter(vector<Person> persons)
		{
			vector<Person> filterPerson;
			for(int persons_i = 0; persons_i < persons.size(); ++persons_i)
			{
				Person person = persons[persons_i];
				if(person.getAge() == this->filterAge){
					filterPerson.push_back(persons[persons_i]);
				}
			}
			return filterPerson;
		}
		
	private:
		int filterAge;
}; 

class SexFilter: public Filter{
	public:
		SexFilter(string sex)
		{
			this->sex = sex;
		}
		
		vector<Person> filter(vector<Person> persons)
		{
			vector<Person> filterPerson;
			for(int persons_i = 0; persons_i < persons.size(); ++persons_i)
			{
				if(persons[persons_i].getSex() == this->sex){
					filterPerson.push_back(persons[persons_i]);
				}
			}
			return filterPerson;
		}
		
	private:
		string sex;
}; 

class AndFilter:public Filter{
	public:
		AndFilter(vector<Filter*> andFilter)
		{
			this->andFilter.swap(andFilter);
		}
		
		vector<Person> filter(vector<Person> persons)
		{
			vector<Person> filterPerson;
			filterPerson.swap(persons);
			for(int andFilter_i = 0; andFilter_i < this->andFilter.size(); ++andFilter_i)
			{
				filterPerson = andFilter[andFilter_i]->filter(filterPerson);
			}
			return filterPerson;
		}
		
	private:
		vector<Filter*> andFilter; 
};

class OrFilter:public Filter{
};


int main()
{
	Person person1 = Person("11",1,"1");
	Person person2 = Person("22",2,"1");
	Person person3 = Person("33",3,"2");
	Person person4 = Person("44",4,"2");
	Person person5 = Person("55",5,"2");
	vector<Person> persons;
	persons.push_back(person1);
	persons.push_back(person2);
	persons.push_back(person3);
	persons.push_back(person4);
	persons.push_back(person5);
	
	
	Filter* nameFilter = new NameFilter("55");
	Filter* ageFilter = new AgeFilter(5);
	Filter* sexFilter = new SexFilter("2");
	vector<Filter*> filters;
	filters.push_back(nameFilter);
	filters.push_back(ageFilter);
	filters.push_back(sexFilter);
	
	Filter* andFilter = new AndFilter(filters);
	vector<Person> personFilter = andFilter->filter(persons);
	for(int personFilter_i = 0; personFilter_i < personFilter.size(); ++personFilter_i)
	{
		cout<<personFilter[personFilter_i].getName() << " " << personFilter[personFilter_i].getAge() << " " << personFilter[personFilter_i].getSex() <<endl;
  	}
	return 0;
} 
