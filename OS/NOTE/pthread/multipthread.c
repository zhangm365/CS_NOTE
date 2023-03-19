
#define NUM_THREAD 100
pthread_t thread_id[NUM_THREAD];

for (int i = 0; i < NUM_THREAD; i++) {
    if (i % 2) {
        pthread_create(thread_id[i], NULL, thread_inc, NULL);
    } else {
        pthread_create(thread_id[i], NULL, thread_dec, NULL);
    }    
}

void* thread_inc(void* arg) {
    for(int i = 0; i < 500000000; ++i) {
        num += 1;
    }
    return NULL;
}

void* thread_dec(void* arg) {
    for(int i = 0; i < 500000000; ++i) {
        num -= 1;
    }
    return NULL;
}