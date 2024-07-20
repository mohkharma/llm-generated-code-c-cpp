#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

typedef struct {
    int n;
    sem_t zeroSem;
    sem_t evenSem;
    sem_t oddSem;
} ZeroEvenOdd;

ZeroEvenOdd* zeroEvenOddCreate(int n) {
    ZeroEvenOdd* obj = (ZeroEvenOdd*)malloc(sizeof(ZeroEvenOdd));
    obj->n = n;
    sem_init(&obj->zeroSem, 0, 1);
    sem_init(&obj->evenSem, 0, 0);
    sem_init(&obj->oddSem, 0, 0);
    return obj;
}

void zero(ZeroEvenOdd* obj, void (*printNumber)(int)) {
    for (int i = 0; i < obj->n; i++) {
        sem_wait(&obj->zeroSem);
        printNumber(0);
        if (i % 2 == 0) {
            sem_post(&obj->oddSem);
        } else {
            sem_post(&obj->evenSem);
        }
    }
}

void even(ZeroEvenOdd* obj, void (*printNumber)(int)) {
    for (int i = 2; i <= obj->n; i += 2) {
        sem_wait(&obj->evenSem);
        printNumber(i);
        sem_post(&obj->zeroSem);
    }
}

void odd(ZeroEvenOdd* obj, void (*printNumber)(int)) {
    for (int i = 1; i <= obj->n; i += 2) {
        sem_wait(&obj->oddSem);
        printNumber(i);
        sem_post(&obj->zeroSem);
    }
}