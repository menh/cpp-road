#include <iostream>
#include <stdarg.h>
#include <pthread.h>
#include <thread>
#include <cstdatomic>
using namespace std;

static long long total = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void* func(void*)
{
	long long i;
	for(i = 0; i < 100000LL; ++i)
	{
		pthread_mutex_lock(&m);
		total += i;
		pthread_mutex_unlock(&m);
	}
}

atomic long total1(0);

void func1(int)
{
	for(long long i = 0; i < 100000LL; ++i)
	{
		total1 += i;
	}
}


int main()
{
	pthread_t thread1, thread2;
	if(pthread_create(&thread1,NULL,&func,NULL)){
		throw;
	}
	if(pthread_create(&thread2,NULL,&func,NULL)){
		throw;
	}
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	cout<<total<<endl;
	return 0;
}
