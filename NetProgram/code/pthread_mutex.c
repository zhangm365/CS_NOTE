/*
	linux下pthread　API
1.创建一个线程
	pthread_create

	NAME
       pthread_create - create a new thread

	pthread_t 类型用来表示线程ID
	pthread_attr_t  类型用来表示线程属性信息

	SYNOPSIS
       #include <pthread.h>

       int pthread_create(pthread_t *thread, 
       			const pthread_attr_t *attr,
                          	void *(*start_routine) (void *), 
                          	void *arg);
                        thread:一个pthread_t类型的指针，用来保存新创建的线程的ID号
                        attr:一个pthread_attr_t类型的指针，表示新创建的线程要采用的
                        		线程属性。这个可以为NULL(一般也为NULL), 表示采用系统
                        		默认属性。
                        start_routine: 函数指针。指向一个带void*参数并且返回一个void*
                        		的类型的函数。该函数即是新创建的线程的指令序列。
                        		也就是新创建的线程要执行的函数。
                        arg: 一个void*指针。该参数在新线程创建后将传给线程函数
                        	作业线程函数的参数。

			返回值:
				成功返回0,
				失败返回-1, errno被设置。

                      

       Compile and link with -lpthread.


2. 线程退出
	(1)线程函数执行完了。
	(2) pthread_exit .在线程函数内部任一时刻调用这个函数都会
		使调用线程退出。

	NAME
       pthread_exit - terminate calling thread

	SYNOPSIS
       #include <pthread.h>

       void pthread_exit(void *retval);
       	retval:线程退出的退出码

       Compile and link with -pthread.

3.  pthread_join 用来等待一个线程退出
	NAME
       pthread_join - join with a terminated thread

SYNOPSIS
       #include <pthread.h>

       int pthread_join(pthread_t thread, void **retval);
       	thread:要等待退出的那个线程的ID
       	retval: 一个二级指针。用来保存退出线程的返回值

       	返回值:
       		成功返回0
       		失败返回一个错误码

       	该函数会阻塞调用线程，直到被等待线程退出。

       Compile and link with -pthread.

4. 线程互斥锁
	在pthread里，
		pthread_mutex_t 这种类型表示一个线程互斥锁
		pthread_mutexattr_t 这种类型表示线程互斥锁的属性

	pthread_mutex_init  初始化一个线程互斥	锁

	pthread_mutex_lock        //P操作
	pthread_mutex_trylock  //p操作(不阻塞的p操作)

	pthread_mutex_unlock //V操作

	pthread_mutex_destroy //销毁一个线程互斥锁


NAME
       pthread_mutex_destroy,  pthread_mutex_init  -  destroy and  initialize a mutex

SYNOPSIS
       #include <pthread.h>

		pthread_mutex_destroy用来销毁mutex指向的线程互斥锁
       int pthread_mutex_destroy(pthread_mutex_t *mutex);

       	pthead_mutex_init用来初始化一个线程互斥锁
       int pthread_mutex_init(pthread_mutex_t *restrict mutex,
              const pthread_mutexattr_t *restrict attr);
		mutex:一个pthread_mutex_t的指针，指向要初始化的线程互斥锁
		attr: 一个pthread_mutexattr_t的指针，指向线程互斥锁的属性。
			该参数可以为NULL(一般也为NULL),表示采用默认属性。
		返回值:
		 成功返回0
		 失败返回-1
              
      NAME
       pthread_mutex_lock,      pthread_mutex_trylock,
       pthread_mutex_unlock - lock and unlock a mutex

SYNOPSIS
       #include <pthread.h>

		 p操作
       int pthread_mutex_lock(pthread_mutex_t *mutex);
       int pthread_mutex_trylock(pthread_mutex_t *mutex);
       	pthread_mutex_trylock不阻塞调用线程，能获取锁就获取，
       	不能获取，就直接返回负数.
       	这个函数如果返回0,表示获取该互斥锁。

       	pthread_mutex_lock会阻塞调用线程(在不能获取互斥锁的情况下，阻塞。
       	直到获取到互斥锁或者出错了。)


       	V操作释放互斥锁
       int pthread_mutex_unlock(pthread_mutex_t *mutex);
       	

5. 线程条件变量
	条件变量：
	a.在多线程程序设计中，我们用条件变量来表示某一特定的条件。
　　　　b. 在条件变量上操作：　初始化，　等待(条件产生)　，唤醒(等待条件的线程)

	在 pthread中，条件变量的类型为 pthread_cond_t, 条件变量的操作:
	5.1 初始化/销毁一个条件变量
		pthread_cond_init/pthread_cond_destroy

	NAME
       pthread_cond_destroy, pthread_cond_init - destroy and initialize condition variables

SYNOPSIS
       #include <pthread.h>

		pthread_cond_destroy用来销毁cond指定的条件变量
       int pthread_cond_destroy(pthread_cond_t *cond);

       	pthread_cond_init用来初始化cond指定的条件变量
       int pthread_cond_init(pthread_cond_t *restrict cond, const pthread_condattr_t *restrict attr);
		cond:指向要初始化的条件变量.
		attr:指向条件变量属性结构体。一般为NULL,
			用默认属性去初始化cond这个条件变量　

	　返回值:
		成功返回0,
		失败返回-1, errno被设置
       	
        //pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

        5.2 等待一个条件(产生)
	NAME
       pthread_cond_timedwait, pthread_cond_wait - wait on a condition

	SYNOPSIS
       #include <pthread.h>

		有一个时间限制的等待条件变量。
       int  pthread_cond_timedwait(pthread_cond_t  *restrict cond,
              			pthread_mutex_t *restrict mutex,
              			const struct timespec *restrict abstime);
              cond:要等待的条件变量
              mutex:互斥锁
              abstime: 一个绝对的等待的系统时间。
              	　在linux下，系统时间是自系统启动以来，经历的
              		时间数。abstime是一个绝对的超时时间。
              			struct timespec
              			{
              				time_t tv_sec;  //秒数
               				long tv_nsec; //纳秒
              			}；
              			该结构体不需要自己定义，系统已经帮我定义好了。

              			例子:
              			stuct timespec ts;
					clock_gettime(CLOCK_REALTIME, &ts);
					ts.tv_sec += 5;
		返回值:
			成功返回0,(表示等待条件产生了)
			失败返回-1, errno被设置。
					如果errno == ETIMEDOUT 表示超时了
			

             "死等"
       int pthread_cond_wait(pthread_cond_t *restrict cond,
             				 pthread_mutex_t *restrict mutex);
             		返回值:
			成功返回0,(表示等待条件产生了)
			失败返回-1, errno被设置。

	NOTE:调用上述函数(pthread_cond_wait/pthread_cond_timedout)时，需要把锁住
		的互斥锁传入，上述等待函数，在让线程休眠(让出CPU)前，
		会释放该互斥锁，然后休眠，直到被唤醒，被唤醒返回时，
		再次锁住该互斥锁，并从等待函数返回。

	5.3唤醒条件变量上的等待线程
		pthread_cond_signal/pthread_cond_broadcast
		
	NAME
       pthread_cond_broadcast,  pthread_cond_signal - broadcast or signal a condition

SYNOPSIS
       #include <pthread.h>

		pthread_cond_broadcast唤醒在cond上等待的所有线程
       int pthread_cond_broadcast(pthread_cond_t *cond);

       	pthread_cond_signal唤醒在cond上等待的一个线程()
       int pthread_cond_signal(pthread_cond_t *cond);

		返回值:
			成功返回0,
			失败返回-1, errno被设置

*/

#include <pthread.h>
#include <stdio.h>
#include <errno.h>

//i,全局变量　，在我们这个例子里，它是一个共享资源
//因为两个线程都要访问它。所以，我们要对它加以保护
//
int i = 0; 


//我们在线程内部，可以有如下三种方式去保护共享资源
//sem_t  POSIX 信号量
//semget   system v信号量

//线程互斥锁
pthread_mutex_t i_mutex;//声明一个线程互斥锁i_mutex,用来保护i
					//在对i进行访问的代码前，加一个p操作
					//在对i进行访问的代码后，加一个v操作


void *thread_test(void * data)
 {
 	int d;

	d = *((int *)data);
	printf("d=%d\n",d);
 
 	while(1)
	{
		//p
		pthread_mutex_lock(&i_mutex);
		i = 1024;
		printf("[%s L_%d] i = %d\n", __FUNCTION__,__LINE__, i);
		usleep(10000);
		//v

		pthread_mutex_unlock(&i_mutex);
	}

	return NULL;
 }

int main(int argc, char *argv[])
 {
 	pthread_t pid;
	int r;
	int d = 100;

	pthread_mutex_init(&i_mutex, NULL);

	/*pthread_create用来创建一个新线程*/
	r = pthread_create(
				&pid, /*第一个参数是一个pthead_t *, 用来保存新线程的ID*/
				NULL, /*第二个参数是线程属性，一般为NULL,表示采用默认属性*/
				&thread_test, /*第三个参数是一个函数指针，指向的函数是新线程要执行的函数*/
				(void *)&d		/*第四个参数，一个地址，将作为线程函数的参数*/

	);


	while (1)
	{
		//p
		pthread_mutex_lock(&i_mutex);
		i = 100;
		printf("[%s L_%d] i = %d\n", __FUNCTION__,__LINE__, i);
		usleep(10000);
		//v
		pthread_mutex_unlock(&i_mutex);
	
	}


	pthread_join(pid, NULL);

	pthread_mutex_destroy(&i_mutex);
 }

