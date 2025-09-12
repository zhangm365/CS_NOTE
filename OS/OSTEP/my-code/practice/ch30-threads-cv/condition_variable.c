
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>

#include <unistd.h>
#include <assert.h>
#include "common_threads.h"

volatile int val = 0;

void *child(void *arg) {
    printf("child\n");
    val = 1;
    return NULL;
}

int main() {

    printf("parent begin\n");
    pthread_t c;
    Pthread_create(&c, NULL, child, NULL);
    Pthread_join(c, NULL);

    printf("parent end, the val = %d\n", val);
    return 0;
}

