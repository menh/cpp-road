#include <iostream>
#include<cstdio>
#include<cstdlib>
#include <pthread.h>
using namespace std;
pthread_mutex_t mutex;
class SingleTon
{
	public: 
		static SingleTon * getInstance();
	private:
		SingleTon();
		//把复制构造函数和=操作符也设为私有,防止被复制
		SingleTon(const SingleTon&);
		SingleTon& operator=(const SingleTon&);
		
		static SingleTon* instance ;
};

SingleTon::SingleTon()
{
	
}

SingleTon::SingleTon(const SingleTon& singleTon)
{
	
}

SingleTon& SingleTon::operator=(const SingleTon&){
	
}

SingleTon* SingleTon::instance = nullptr;

SingleTon* SingleTon::getInstance()
{
	if(instance == nullptr)
	{
		pthread_mutex_lock(&mutex);
		if(instance == nullptr)
		{
			instance = new SingleTon();
		}
		pthread_mutex_unlock(&mutex);
	//	unclock();
	}
	return instance;
}



int main()
{
	SingleTon* singleTon1 = SingleTon::getInstance();
	SingleTon* singleTon2 = SingleTon::getInstance();
	cout << (singleTon1 == singleTon2) <<endl;
	
	return 0;
}
