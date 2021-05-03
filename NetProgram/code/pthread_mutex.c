/*
	linux��pthread��API
1.����һ���߳�
	pthread_create

	NAME
       pthread_create - create a new thread

	pthread_t ����������ʾ�߳�ID
	pthread_attr_t  ����������ʾ�߳�������Ϣ

	SYNOPSIS
       #include <pthread.h>

       int pthread_create(pthread_t *thread, 
       			const pthread_attr_t *attr,
                          	void *(*start_routine) (void *), 
                          	void *arg);
                        thread:һ��pthread_t���͵�ָ�룬���������´������̵߳�ID��
                        attr:һ��pthread_attr_t���͵�ָ�룬��ʾ�´������߳�Ҫ���õ�
                        		�߳����ԡ��������ΪNULL(һ��ҲΪNULL), ��ʾ����ϵͳ
                        		Ĭ�����ԡ�
                        start_routine: ����ָ�롣ָ��һ����void*�������ҷ���һ��void*
                        		�����͵ĺ������ú��������´������̵߳�ָ�����С�
                        		Ҳ�����´������߳�Ҫִ�еĺ�����
                        arg: һ��void*ָ�롣�ò��������̴߳����󽫴����̺߳���
                        	��ҵ�̺߳����Ĳ�����

			����ֵ:
				�ɹ�����0,
				ʧ�ܷ���-1, errno�����á�

                      

       Compile and link with -lpthread.


2. �߳��˳�
	(1)�̺߳���ִ�����ˡ�
	(2) pthread_exit .���̺߳����ڲ���һʱ�̵��������������
		ʹ�����߳��˳���

	NAME
       pthread_exit - terminate calling thread

	SYNOPSIS
       #include <pthread.h>

       void pthread_exit(void *retval);
       	retval:�߳��˳����˳���

       Compile and link with -pthread.

3.  pthread_join �����ȴ�һ���߳��˳�
	NAME
       pthread_join - join with a terminated thread

SYNOPSIS
       #include <pthread.h>

       int pthread_join(pthread_t thread, void **retval);
       	thread:Ҫ�ȴ��˳����Ǹ��̵߳�ID
       	retval: һ������ָ�롣���������˳��̵߳ķ���ֵ

       	����ֵ:
       		�ɹ�����0
       		ʧ�ܷ���һ��������

       	�ú��������������̣߳�ֱ�����ȴ��߳��˳���

       Compile and link with -pthread.

4. �̻߳�����
	��pthread�
		pthread_mutex_t �������ͱ�ʾһ���̻߳�����
		pthread_mutexattr_t �������ͱ�ʾ�̻߳�����������

	pthread_mutex_init  ��ʼ��һ���̻߳���	��

	pthread_mutex_lock        //P����
	pthread_mutex_trylock  //p����(��������p����)

	pthread_mutex_unlock //V����

	pthread_mutex_destroy //����һ���̻߳�����


NAME
       pthread_mutex_destroy,  pthread_mutex_init  -  destroy and  initialize a mutex

SYNOPSIS
       #include <pthread.h>

		pthread_mutex_destroy��������mutexָ����̻߳�����
       int pthread_mutex_destroy(pthread_mutex_t *mutex);

       	pthead_mutex_init������ʼ��һ���̻߳�����
       int pthread_mutex_init(pthread_mutex_t *restrict mutex,
              const pthread_mutexattr_t *restrict attr);
		mutex:һ��pthread_mutex_t��ָ�룬ָ��Ҫ��ʼ�����̻߳�����
		attr: һ��pthread_mutexattr_t��ָ�룬ָ���̻߳����������ԡ�
			�ò�������ΪNULL(һ��ҲΪNULL),��ʾ����Ĭ�����ԡ�
		����ֵ:
		 �ɹ�����0
		 ʧ�ܷ���-1
              
      NAME
       pthread_mutex_lock,      pthread_mutex_trylock,
       pthread_mutex_unlock - lock and unlock a mutex

SYNOPSIS
       #include <pthread.h>

		 p����
       int pthread_mutex_lock(pthread_mutex_t *mutex);
       int pthread_mutex_trylock(pthread_mutex_t *mutex);
       	pthread_mutex_trylock�����������̣߳��ܻ�ȡ���ͻ�ȡ��
       	���ܻ�ȡ����ֱ�ӷ��ظ���.
       	��������������0,��ʾ��ȡ�û�������

       	pthread_mutex_lock�����������߳�(�ڲ��ܻ�ȡ������������£�������
       	ֱ����ȡ�����������߳����ˡ�)


       	V�����ͷŻ�����
       int pthread_mutex_unlock(pthread_mutex_t *mutex);
       	

5. �߳���������
	����������
	a.�ڶ��̳߳�������У�������������������ʾĳһ�ض���������
��������b. �����������ϲ���������ʼ�������ȴ�(��������)��������(�ȴ��������߳�)

	�� pthread�У���������������Ϊ pthread_cond_t, ���������Ĳ���:
	5.1 ��ʼ��/����һ����������
		pthread_cond_init/pthread_cond_destroy

	NAME
       pthread_cond_destroy, pthread_cond_init - destroy and initialize condition variables

SYNOPSIS
       #include <pthread.h>

		pthread_cond_destroy��������condָ������������
       int pthread_cond_destroy(pthread_cond_t *cond);

       	pthread_cond_init������ʼ��condָ������������
       int pthread_cond_init(pthread_cond_t *restrict cond, const pthread_condattr_t *restrict attr);
		cond:ָ��Ҫ��ʼ������������.
		attr:ָ�������������Խṹ�塣һ��ΪNULL,
			��Ĭ������ȥ��ʼ��cond�������������

	������ֵ:
		�ɹ�����0,
		ʧ�ܷ���-1, errno������
       	
        //pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

        5.2 �ȴ�һ������(����)
	NAME
       pthread_cond_timedwait, pthread_cond_wait - wait on a condition

	SYNOPSIS
       #include <pthread.h>

		��һ��ʱ�����Ƶĵȴ�����������
       int  pthread_cond_timedwait(pthread_cond_t  *restrict cond,
              			pthread_mutex_t *restrict mutex,
              			const struct timespec *restrict abstime);
              cond:Ҫ�ȴ�����������
              mutex:������
              abstime: һ�����Եĵȴ���ϵͳʱ�䡣
              	����linux�£�ϵͳʱ������ϵͳ����������������
              		ʱ������abstime��һ�����Եĳ�ʱʱ�䡣
              			struct timespec
              			{
              				time_t tv_sec;  //����
               				long tv_nsec; //����
              			}��
              			�ýṹ�岻��Ҫ�Լ����壬ϵͳ�Ѿ����Ҷ�����ˡ�

              			����:
              			stuct timespec ts;
					clock_gettime(CLOCK_REALTIME, &ts);
					ts.tv_sec += 5;
		����ֵ:
			�ɹ�����0,(��ʾ�ȴ�����������)
			ʧ�ܷ���-1, errno�����á�
					���errno == ETIMEDOUT ��ʾ��ʱ��
			

             "����"
       int pthread_cond_wait(pthread_cond_t *restrict cond,
             				 pthread_mutex_t *restrict mutex);
             		����ֵ:
			�ɹ�����0,(��ʾ�ȴ�����������)
			ʧ�ܷ���-1, errno�����á�

	NOTE:������������(pthread_cond_wait/pthread_cond_timedout)ʱ����Ҫ����ס
		�Ļ��������룬�����ȴ������������߳�����(�ó�CPU)ǰ��
		���ͷŸû�������Ȼ�����ߣ�ֱ�������ѣ������ѷ���ʱ��
		�ٴ���ס�û����������ӵȴ��������ء�

	5.3�������������ϵĵȴ��߳�
		pthread_cond_signal/pthread_cond_broadcast
		
	NAME
       pthread_cond_broadcast,  pthread_cond_signal - broadcast or signal a condition

SYNOPSIS
       #include <pthread.h>

		pthread_cond_broadcast������cond�ϵȴ��������߳�
       int pthread_cond_broadcast(pthread_cond_t *cond);

       	pthread_cond_signal������cond�ϵȴ���һ���߳�()
       int pthread_cond_signal(pthread_cond_t *cond);

		����ֵ:
			�ɹ�����0,
			ʧ�ܷ���-1, errno������

*/

#include <pthread.h>
#include <stdio.h>
#include <errno.h>

//i,ȫ�ֱ�������������������������һ��������Դ
//��Ϊ�����̶߳�Ҫ�����������ԣ�����Ҫ�������Ա���
//
int i = 0; 


//�������߳��ڲ����������������ַ�ʽȥ����������Դ
//sem_t  POSIX �ź���
//semget   system v�ź���

//�̻߳�����
pthread_mutex_t i_mutex;//����һ���̻߳�����i_mutex,��������i
					//�ڶ�i���з��ʵĴ���ǰ����һ��p����
					//�ڶ�i���з��ʵĴ���󣬼�һ��v����


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

	/*pthread_create��������һ�����߳�*/
	r = pthread_create(
				&pid, /*��һ��������һ��pthead_t *, �����������̵߳�ID*/
				NULL, /*�ڶ����������߳����ԣ�һ��ΪNULL,��ʾ����Ĭ������*/
				&thread_test, /*������������һ������ָ�룬ָ��ĺ��������߳�Ҫִ�еĺ���*/
				(void *)&d		/*���ĸ�������һ����ַ������Ϊ�̺߳����Ĳ���*/

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

