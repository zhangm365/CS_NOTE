

#include<iostream>
#include<pthread.h>
#include "semaphore.h"
using namespace std;

int sem1, sem2;
//int n = 10;  /*1...n的平均值*/
int sum = 0;
double average = 0;

void* t1(void* arg)
{
	void* tmp = arg;
	int n = *((int *)tmp);

	for(int i=1; i <= n; ++i)
		sum += i;
	sem_v(sem1);  /*V操作，通知t2求和已完成*/ 

	return arg;

}

void* t2(void* arg)
{
	void* tmp = arg;
	int n = *((int *)tmp);
	sem_p(sem1);  /*P操作，等待t1完成*/	
	average = (double)sum/n;
	sem_v(sem2);  /*V操作，通知main求平均已完成*/

	return arg;

}

int main( int argc, const char* argv[] )
{

	if( argc < 2 ) 
	{
		printf("Info: %s number\n", argv[0]);
		return -1;

	}

	int n = stoi(argv[1]);

	sem1 = creat_sem("/" , 0); /*创建信号量*/
	sem2 = creat_sem("/home", 0);

	pthread_t id[2];
	pthread_create(&id[0], NULL, t1, (void*)&n);
	pthread_create(&id[1], NULL, t2, (void*)&n);

	sem_p(sem2);  /*P操作，等待t2完成*/
	cout << "The sum is: " << sum << endl;
	cout << "The average is: " << average << endl;

	del_sem(sem1); /*删除信号量*/
	del_sem(sem2);
	return 0;
}