#include <pthread.h>
#include <stdio.h>

typedef struct {
    int n;
    int current;
    pthread_mutex_t mutex;
    pthread_cond_t zero_cond;
    pthread_cond_t even_cond;
    pthread_cond_t odd_cond;
} ZeroEvenOdd;

ZeroEvenOdd* zeroEvenOddCreate(int n) {
    ZeroEvenOdd* obj = (ZeroEvenOdd*)malloc(sizeof(ZeroEvenOdd));
    obj->n = n;
    obj->current = 0;
    pthread_mutex_init(&obj->mutex, NULL);
    pthread_cond_init(&obj->zero_cond, NULL);
    pthread_cond_init(&obj->even_cond, NULL);
    pthread_cond_init(&obj->odd_cond, NULL);
    return obj;
}

void zero(ZeroEvenOdd* obj, void (*printNumber)(int)) {
    for (int i = 0; i < obj->n; ++i) {
        pthread_mutex_lock(&obj->mutex);
        while (obj->current % 2 != 0) {
            pthread_cond_wait(&obj->zero_cond, &obj->mutex);
        }
        printNumber(0);
        obj->current++;
        if (obj->current % 2 == 0) {
            pthread_cond_signal(&obj->even_cond);
        } else {
            pthread_cond_signal(&obj->odd_cond);
        }
        pthread_mutex_unlock(&obj->mutex);
    }
}

void even(ZeroEvenOdd* obj, void (*printNumber)(int)) {
    for (int i = 2; i <= obj->n; i += 2) {
        pthread_mutex_lock(&obj->mutex);
        while (obj->current % 4 != 2) {
            pthread_cond_wait(&obj->even_cond, &obj->mutex);
        }
        printNumber(i);
        obj->current++;
        pthread_cond_signal(&obj->zero_cond);
        pthread_mutex_unlock(&obj->mutex);
    }
}

void odd(ZeroEvenOdd* obj, void (*printNumber)(int)) {
    for (int i = 1; i <= obj->n; i += 2) {
        pthread_mutex_lock(&obj->mutex);
        while (obj->current % 4 != 1) {
            pthread_cond_wait(&obj->odd_cond, &obj->mutex);
        }
        printNumber(i);
        obj->current++;
        pthread_cond_signal(&obj->zero_cond);
        pthread_mutex_unlock(&obj->mutex);
    }
}

void zeroEvenOddFree(ZeroEvenOdd* obj) {
    pthread_mutex_destroy(&obj->mutex);
    pthread_cond_destroy(&obj->zero_cond);
    pthread_cond_destroy(&obj->even_cond);
    pthread_cond_destroy(&obj->odd_cond);
    free(obj);
}