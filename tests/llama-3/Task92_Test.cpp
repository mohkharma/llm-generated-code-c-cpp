#include <iostream>
#include <thread>
#include <mutex>

std::mutex lock;
int maxCounter = 5;
int currentCounter = 0;

void accessResource(int threadId) {
    while (currentCounter <= maxCounter) {
        std::lock_guard<std::mutex> guard(lock);
        if (currentCounter <= maxCounter) {
            currentCounter++;
            std::cout << "Thread " << threadId << " is accessing the currentCounter at " << currentCounter << std::endl;
        } else {
            break;
        }
    }
}

int main() {
    std::thread threads[5];
    for (int i = 0; i < 5; i++) {
        threads[i] = std::thread(accessResource, i);
    }
    for (auto& t : threads) {
        t.join();
    }

    if (currentCounter <= maxCounter + 1) {
        std::cout << "Test case result: PASS" << std::endl;
    } else {
        std::cout << "Test case result: FAIL" << std::endl;
    }

    return 0;
}
