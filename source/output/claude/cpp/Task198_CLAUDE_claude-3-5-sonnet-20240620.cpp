
#include <iostream>
#include <vector>
#include <random>

int rand7() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(1, 7);
    return dis(gen);
}

int rand10() {
    while (true) {
        int result = (rand7() - 1) * 7 + (rand7() - 1);
        if (result < 40) {
            return result % 10 + 1;
        }
    }
}
