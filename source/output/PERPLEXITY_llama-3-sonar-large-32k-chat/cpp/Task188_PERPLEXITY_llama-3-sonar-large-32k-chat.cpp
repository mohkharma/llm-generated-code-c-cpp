#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>

class FooBar {
private:
    int n;
    std::mutex mtx;
    std::condition_variable cv;
    bool fooLock = true;

public:
    FooBar(int n) : n(n) {}

    void foo(std::function<void()> printFoo) {
        for (int i = 0; i < n; i++) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this] { return fooLock; });
            printFoo();
            fooLock = false;
            cv.notify_all();
        }
    }

    void bar(std::function<void()> printBar) {
        for (int i = 0; i < n; i++) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this] { return !fooLock; });
            printBar();
            fooLock = true;
            cv.notify_all();
        }
    }
};
