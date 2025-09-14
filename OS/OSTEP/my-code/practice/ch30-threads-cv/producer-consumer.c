
/**
 * @author: zhangm365
 * @file: producer-consumer.c
 * @brief: condition variable about producer and consumer. 
 * see reference: https://pages.cs.wisc.edu/~remzi/OSTEP/threads-cv.pdf
 *
 */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "common_threads.h"


const int MAX = 128;
int buffer[MAX];

int fill = 0;
int use = 0;
int count = 0;

/**
 * @brief 两个条件变量，以便正确发出信号：区别哪类线程应该被唤醒。
 * 1. cv_empty: 缓冲区有空闲位置；2. cv_fill: 填充缓冲区。
 * 
 */

pthread_cond_t cv_empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t cv_fill = PTHREAD_COND_INITIALIZER;

// 互斥锁
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void put(int value) {
    buffer[fill] = value;
    fill = (fill + 1) % MAX;
    count++;
}

int get() {

    int tmp = buffer[use];
    use = (use + 1) % MAX;
    count--;
    return tmp;
}

/**
 * @brief: 生产者
 * 等待 cv_empty 变量，发信号给 cv_fill 变量。
 * @param arg 
 * @return void* 
 */

void *producer(void *arg) {

    int loops = *((int *)arg);
    for (int i = 0; i < loops; ++i) {

        Pthread_mutex_lock(&mtx);
        while (count == MAX) {  // while loop
            Pthread_cond_wait(&cv_empty, &mtx);
        }

        put(i);
        Pthread_cond_signal(&cv_fill);
        Pthread_mutex_unlock(&mtx);
    }

    return NULL;

}

/**
 * @brief: 消费者
 * 等待 cv_fill 变量，发信号给 cv_empty 变量。
 * @param arg 
 * @return void* 
 */

void *consumer(void *arg) {

    int loops = *((int *)arg);
    for (int i = 0; i < loops; ++i) {
        Pthread_mutex_lock(&mtx);
        while (count == 0) {
            pthread_cond_wait(&cv_fill, &mtx);
        }

        int tmp = get();
        Pthread_cond_signal(&cv_empty);
        pthread_mutex_unlock(&mtx);
        printf("%d\n", tmp);
    }

    return NULL;

}

int main () {

    pthread_t pt_c1, pt_c2;
    pthread_t pt_p;

    int c_num = 64;
    int p_num = 128;

    Pthread_create(&pt_p, NULL, producer, &p_num);
    Pthread_create(&pt_c1, NULL, consumer, &c_num);
    Pthread_create(&pt_c2, NULL, consumer, &c_num);

    Pthread_join(pt_p, NULL);
    Pthread_join(pt_c1, NULL);
    Pthread_join(pt_c2, NULL);

    return 0;
}