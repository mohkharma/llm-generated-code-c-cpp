#include <functional>
#include <mutex>
#include <condition_variable>
#include <thread>

using namespace std;

class ZeroEvenOdd {
private:
    int n;
    int current;
    mutex m;
    condition_variable cv;
    bool zeroTurn;

public:
    ZeroEvenOdd(int n) : n(n), current(1), zeroTurn(true) {}

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
        for (int i = 0; i < n; ++i) {
            unique_lock<mutex> lock(m);
            cv.wait(lock, [this]() { return zeroTurn; });
            printNumber(0);
            zeroTurn = false;
            cv.notify_all();
        }
    }

    void even(function<void(int)> printNumber) {
        for (int i = 2; i <= n; i += 2) {
            unique_lock<mutex> lock(m);
            cv.wait(lock, [this]() { return !zeroTurn && current % 2 == 0; });
            printNumber(current++);
            zeroTurn = true;
            cv.notify_all();
        }
    }

    void odd(function<void(int)> printNumber) {
        for (int i = 1; i <= n; i += 2) {
            unique_lock<mutex> lock(m);
            cv.wait(lock, [this]() { return !zeroTurn && current % 2 != 0; });
            printNumber(current++);
            zeroTurn = true;
            cv.notify_all();
        }
    }
};