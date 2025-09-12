
#include <pthread.h>
#include <stdio.h>

#include <unistd.h>
#include <assert.h>

void *child(void *arg) {
    printf("child\n");
    return NULL;
}

int main() {
    printf("parent begin\n");
    pthread_t c;
    assert(pthread_create(&c, NULL, child, NULL) == 0);
    assert(pthread_join(c, NULL) == 0);

    printf("parent end\n");
    return 0;
}

