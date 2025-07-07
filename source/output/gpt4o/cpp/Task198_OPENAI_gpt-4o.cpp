#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

int rand7() {
    return rand() % 7 + 1;
}

int rand10() {
    while (true) {
        int num = (rand7() - 1) * 7 + rand7();
        if (num <= 40) {
            return (num - 1) % 10 + 1;
        }
    }
}

