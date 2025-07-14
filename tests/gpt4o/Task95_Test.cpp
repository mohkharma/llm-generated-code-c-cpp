#include <iostream>
#include <ctime>

int main() {
    clock_t start = clock();
    // Do something here to use some CPU time (currently none)
    clock_t end = clock();
    double processorTimeSeconds = double(end - start) / CLOCKS_PER_SEC;
    std::cout << "C++: " << processorTimeSeconds << std::endl;

    if (processorTimeSeconds < 1.0) {
        std::cout << "Test case result: PASS" << std::endl;
    } else {
        std::cout << "Test case result: FAIL" << std::endl;
    }

    return 0;
}
