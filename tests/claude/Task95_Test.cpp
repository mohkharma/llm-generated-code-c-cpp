#include <iostream>
#include <ctime>

int main() {
    std::clock_t cpu_time = std::clock();
    double seconds = static_cast<double>(cpu_time) / CLOCKS_PER_SEC;

    std::cout << seconds << std::endl;

    if (seconds < 1.0) {
        std::cout << "Test case result: PASS" << std::endl;
    } else {
        std::cout << "Test case result: FAIL" << std::endl;
    }

    return 0;
}
