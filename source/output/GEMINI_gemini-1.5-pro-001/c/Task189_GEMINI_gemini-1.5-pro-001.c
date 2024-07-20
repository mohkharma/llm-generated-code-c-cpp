#include <stdio.h>
#include <pthread.h>

typedef struct {
    int n;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int turn;
} ZeroEvenOddArgs;

void* zero(void* args) {
    ZeroEvenOddArgs* arg = (ZeroEvenOddArgs*)args;
    for (int i = 1; i <= arg->n; ++i) {
        pthread_mutex_lock(&arg->mutex);
        while (arg->turn != 0) {
            pthread_cond_wait(&arg->cond, &arg->mutex);
        }
        printf("0");
        arg->turn = (i % 2 == 0) ? 2 : 1;
        pthread_cond_broadcast(&arg->cond);
        pthread_mutex_unlock(&arg->mutex);
    }
    return NULL;
}

void* even(void* args) {
    ZeroEvenOddArgs* arg = (ZeroEvenOddArgs*)args;
    for (int i = 2; i <= arg->n; i += 2) {
        pthread_mutex_lock(&arg->mutex);
        while (arg->turn != 2) {
            pthread_cond_wait(&arg->cond, &arg->mutex);
        }
        printf("%d", i);
        arg->turn = 0;
        pthread_cond_broadcast(&arg->cond);
        pthread_mutex_unlock(&arg->mutex);
    }
    return NULL;
}

void* odd(void* args) {
    ZeroEvenOddArgs* arg = (ZeroEvenOddArgs*)args;
    for (int i = 1; i <= arg->n; i += 2) {
        pthread_mutex_lock(&arg->mutex);
        while (arg->turn != 1) {
            pthread_cond_wait(&arg->cond, &arg->mutex);
        }
        printf("%d", i);
        arg->turn = 0;
        pthread_cond_broadcast(&arg->cond);
        pthread_mutex_unlock(&arg->mutex);
    }
    return NULL;
}

int main() {
    int n = 5;
    ZeroEvenOddArgs args;
    args.n = n;
    pthread_mutex_init(&args.mutex, NULL);
    pthread_cond_init(&args.cond, NULL);
    args.turn = 0;

    pthread_t zeroThread, evenThread, oddThread;
    pthread_create(&zeroThread, NULL, zero, &args);
    pthread_create(&evenThread, NULL, even, &args);
    pthread_create(&oddThread, NULL, odd, &args);

    pthread_join(zeroThread, NULL);
    pthread_join(evenThread, NULL);
    pthread_join(oddThread, NULL);

    pthread_mutex_destroy(&args.mutex);
    pthread_cond_destroy(&args.cond);
    return 0;
}