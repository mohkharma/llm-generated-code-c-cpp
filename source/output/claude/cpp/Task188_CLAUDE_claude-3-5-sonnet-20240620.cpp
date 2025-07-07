
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>

class FooBar {
private:
    int n;
    std::mutex mtx;
    std::condition_variable cv;
    bool fooTurn = true;

public:
    FooBar(int n) {
        this->n = n;
    }

    void foo(std::function<void()> printFoo) {
        for (int i = 0; i < n; i++) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this] { return fooTurn; });
            printFoo();
            fooTurn = false;
            cv.notify_all();
        }
    }

    void bar(std::function<void()> printBar) {
        for (int i = 0; i < n; i++) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this] { return !fooTurn; });
            printBar();
            fooTurn = true;
            cv.notify_all();
        }
    }
};