#include <iostream>
using namespace std;

typedef struct condition{
	pthread_mutex_t pmutex;
	pthread_cond_t pcond;
}condition_t;

typedef struct task{
	void *(*run)(void *args);  //����ָ�룬��Ҫִ�е�����
    void *arg;              //����
    struct task *next;      //�����������һ������
}task_t;

typedef struct threadpool{
	condition_t ready;
}threadpool_t;

int main()
{
	
	return 0;
} 
