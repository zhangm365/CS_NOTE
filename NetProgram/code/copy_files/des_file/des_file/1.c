#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include <errno.h>
#include <pthread.h>

#define MAX_WAITING_TASKS	1000
#define MAX_ACTIVE_THREADS	20

#define BUFSIZE			100
#define PATHSIZE		100

struct task
{
	void *(*do_task)(void *arg); //函数指针，指向任务要执行的函数
	void *arg;  //一个指针，任务执行函数时作业函数的参数传入

	struct task *next;
};

typedef struct thread_pool
{
	pthread_mutex_t lock; //互斥锁，用来保护这个"线程池"，就是保护这个链表的　
	pthread_cond_t  cond; //　有任务的条件　

	bool shutdown;  //是否退出。

	struct task *task_list;	//任务链表

	pthread_t *tids;  //指向线程ID的数组，因为我可能会创建多个线程。

	unsigned int max_waiting_tasks;	//表示最大的任务数
	unsigned int waiting_tasks; 	//目前正在链表上的任务数
	unsigned int active_threads; 	//正在服役的线程数

}thread_pool;


bool init_pool(thread_pool *pool, unsigned int threads_number);
bool add_task(thread_pool *pool, void *(*do_task)(void *arg), void *task);
int  add_thread(thread_pool *pool, unsigned int additional_threads_number);
int  remove_thread(thread_pool *pool, unsigned int removing_threads_number);
bool destroy_pool(thread_pool *pool);

void *routine(void *arg);


#endif
