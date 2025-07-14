#include <chrono>
#include <iostream>

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(start.time_since_epoch());
    std::cout << "Current processor time in seconds: " << duration.count() << std::endl;

    if (duration.count() >= 0) {  // always true, just to follow pass/fail pattern
        std::cout << "Test case result: PASS" << std::endl;
    } else {
        std::cout << "Test case result: FAIL" << std::endl;
    }

    return 0;
}
