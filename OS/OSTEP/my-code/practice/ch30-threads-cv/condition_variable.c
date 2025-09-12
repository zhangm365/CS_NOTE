/**
 * condition variables
 * @file
 * @brief
 *
 */

#include <pthread.h>
#include <stdint.h>
#include <stdio.h>

#include <sys/_pthread/_pthread_cond_t.h>
#include <sys/_pthread/_pthread_mutex_t.h>
#include <unistd.h>
#include <assert.h>
#include "common_threads.h"

volatile int val = 0;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void thr_exit() {
    Pthread_mutex_lock(&lock);
    val = 1;
    Pthread_cond_signal(&cond);
    Pthread_mutex_unlock(&lock);
}

void *child(void *arg) {
    printf("child\n");
    thr_exit();
    return NULL;
}

void thr_join() {
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
    // Pthread_join(c, NULL);
    thr_join();
    printf("parent end, the val = %d\n", val);
    return 0;
}

