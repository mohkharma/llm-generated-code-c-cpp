#include <iostream>
#include <cstdlib>
#include <ctime>

int rand7() {
    return rand() % 7 + 1;
}

int rand10() {
    srand(static_cast<unsigned int>(time(0)));
    while (true) {
        int num = (rand7() - 1) * 7 + rand7();
        if (num <= 40) {
            return num % 10 + 1;
        }
    }
}

int main() {
    int n = 1;  // change this to test with different inputs
    for (int i = 0; i < n; i++) {
        std::cout << rand10() << " ";
    }
    return 0;
}