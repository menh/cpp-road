#include <iostream>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

typedef struct condition{
	pthread_mutex_t pmutex;
	pthread_cond_t pcond;
}condition_t;

int condition_init(condition_t* cond)
{
	int status;
	if(status = pthread_mutex_init(&cond->pmutex, NULL))
		return status;
	if(status = pthread_cond_init(&cond->pcond, NULL))
		return status;
	return 0;
}

int condition_lock(condition_t* cond)
{
	return pthread_mutex_lock(&cond->pmutex);
}

int condition_signal(condition_t* cond)
{
	return pthread_cond_signal(&cond->pcond);
}

int condition_unlock(condition_t* cond)
{
	return pthread_mutex_unlock(&cond->pmutex);
}

int condition_timewait(condition_t* cond, const struct timespec* abstime)
{
	return pthread_cond_timedwait(&cond->pcond, &cond->pmutex, abstime); //https://blog.csdn.net/whz_zb/article/details/6937673 pthread_cond_timedwait 实例
}

typedef struct task{
	void *(*run)(void *args);  //函数指针，需要执行的任务
    void *arg;              //参数
    struct task *next;      //任务队列中下一个任务
}task_t;

 
class CThreadpool{
	public:
		condition_t ready;
		task_t* first;
		task_t* last;
		int counter;
		int idle;
		int max_threads;
		int quit;
	public:
		void threadpool_init(int threads);
		void threadpool_add_task(void *(*run)(void *arg), void *arg);
		void threadpool_destory(CThreadpool* pool);
}; 
 
void CThreadpool::threadpool_init(int threads)
{
	condition_init(&this->ready);
	this->first = NULL;
	this->last = NULL;
	this->counter = 0;
	this->idle = 0;
	this->max_threads = threads;
	this->quit = 0;
}
void *thread_routine(void *arg);
void CThreadpool::threadpool_add_task(void *(*run)(void *arg), void *arg)
{
	//创建一个任务 
	
	task_t* newTask = (task_t*)malloc(sizeof(task_t));
	newTask->run = run;
	newTask->arg = arg;
	newTask->next = NULL;
	//p(mutex) 
	condition_lock(&this->ready);
	
	if(this->first == NULL)
	{
		this->first = newTask;
	}
	else
	{
		this->last->next = newTask;
	}
	this->last = newTask;
	
	if(this->idle > 0)
	{
		//v(cond)
		condition_signal(&this->ready);
	}
	else if(this->counter < this->max_threads)
	{
//		cout<<"创建一个任务"<<endl;
		pthread_t tid;
		pthread_create(&tid, NULL, thread_routine, this);
		this->counter ++;
	}
	condition_unlock(&this->ready);
}

void *thread_routine(void *arg)
{
	struct timespec abstime; //https://blog.csdn.net/liu44235/article/details/37692635 struct timespec 和 struct timeval
	int timeout;
	//cout<<"thread %d is starting "<< (int)pthread_self() <<endl;
	printf("thread %d is starting\n", (int)pthread_self());
//	cout<<"csdfd"<<endl;
//	cout<<"thread %d is starting "<< (int)pthread_self() <<endl;
	CThreadpool* pool = (CThreadpool*) arg;
	while(1)
	{
		timeout = 0;
		
		//p(mutex)
		condition_lock(&pool->ready);
		
		pool->idle++;
		
		//如果线程池没有任务，则结束 
		while(pool->first == NULL && !pool->quit)
		{
			printf("thread %d is waiting\n", (int)pthread_self());
			
			clock_gettime(CLOCK_REALTIME, &abstime);
			
			abstime.tv_sec += 2;
			int status = condition_timewait(&pool->ready, &abstime);
			if(status == ETIMEDOUT)
			{
				printf("thread %d wait time out\n", (int)pthread_self());
				timeout = 1;
				break;
			}	
		}
		
		 	
		pool->idle--;
		if(pool->first != NULL)
		{
			task_t* t = pool->first;
			pool->first = t->next;
			
			condition_unlock(&pool->ready);
			
			t->run(t->arg);
			
			free(t);
			
			condition_lock(&pool->ready);
		}
		
		if(pool->quit && pool->first == NULL)
		{
			pool->counter--;
			if(pool->counter ==0)
			{
				condition_signal(&pool->ready);
			}
			condition_unlock(&pool->ready);
			break;
			
		} 
		if(timeout == 1)
		{
			pool->counter -- ;
			condition_unlock(&pool->ready);
			break;
		}
		condition_unlock(&pool->ready);
	}
	printf("thread %d is exiting\n", (int)pthread_self());
    return NULL;
}
void* mytask(void *arg)
{
	//cout<<"mytask"<<endl;
    //printf("thread %d is working on task %d\n", (int)pthread_self(), *(int*)arg);
    sleep(1); 
    free(arg);
    return NULL;
}
int main()
{
	CThreadpool pool;
	pool.threadpool_init(3);
	int i = 0;
	
	for(i = 0; i < 1; i++)
	{
		int *arg = (int*)malloc(sizeof(int));
		*arg = i;
		pool.threadpool_add_task(mytask, arg);
	}
	while(1)
	{
		
	}
	//sleep(100);
	return 0;
} 
