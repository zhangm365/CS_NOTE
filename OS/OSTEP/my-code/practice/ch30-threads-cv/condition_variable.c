/**
 * condition variables
 * @author: zhangm365
 * @file: condition_variable.c
 * @brief: condition variable. https://pages.cs.wisc.edu/~remzi/OSTEP/threads-cv.pdf
 *
 */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include "common_threads.h"

int val = 0;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void thr_process() {
    Pthread_mutex_lock(&lock);
    val = 1;
    Pthread_cond_signal(&cond);
    Pthread_mutex_unlock(&lock);
}

void *child(void *arg) {
    printf("child\n");
    thr_process();
    return NULL;
}

void thr_wait() {
    Pthread_mutex_lock(&lock);
    while (val == 0) {
        pthread_cond_wait(&cond, &lock);
    }

    Pthread_mutex_unlock(&lock);
}

int main() {

    printf("parent begin\n");
    pthread_t c;
    Pthread_create(&c, NULL, child, NULL);

    thr_wait();
    printf("parent end, the val = %d\n", val);
    // 等待子线程正常退出.
    Pthread_join(c, NULL);
    return 0;
}

