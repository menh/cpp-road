#include <iostream>
using namespace std;

typedef struct condition{
	pthread_mutex_t pmutex;
	pthread_cond_t pcond;
}condition_t;

typedef struct task{
	void *(*run)(void *args);  //函数指针，需要执行的任务
    void *arg;              //参数
    struct task *next;      //任务队列中下一个任务
}task_t;

typedef struct threadpool{
	condition_t ready;
}threadpool_t;

int main()
{
	
	return 0;
} 
