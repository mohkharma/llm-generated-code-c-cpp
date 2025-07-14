#include <iostream>
#include <thread>
#include <mutex>

int maxCounter = 10;
int currentCounter = 0;
std::mutex counterMutex;

void worker(int thread_id) {
    while (true) {
        std::lock_guard<std::mutex> lock(counterMutex);
        if (currentCounter <= maxCounter) {
            std::cout << "Thread " << thread_id << " accessing currentCounter: " << currentCounter << std::endl;
            currentCounter++;
        } else {
            break;
        }
    }
}

int main() {
    std::thread threads[5];

    for (int i = 0; i < 5; ++i) {
        threads[i] = std::thread(worker, i);
    }

    for (int i = 0; i < 5; ++i) {
        threads[i].join();
    }

    // بعد انتهاء جميع الثريدات، نتحقق إذا currentCounter تجاوز maxCounter
    if (currentCounter > maxCounter + 1) {
        std::cout << "Test case result: FAIL" << std::endl;
    } else {
        std::cout << "Test case result: PASS" << std::endl;
    }

    return 0;
}
