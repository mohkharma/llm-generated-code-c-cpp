#include <mutex>
#include <condition_variable>
#include <functional>
#include <thread>

class H2O {
public:
    H2O() : hCount(0), oCount(0) {}

    void hydrogen(std::function<void()> releaseHydrogen) {
        std::unique_lock<std::mutex> lock(m);
        cv.wait(lock, [this] { return (hCount < 2 && oCount == 0) || (hCount == 2 && oCount == 1); });
        // releaseHydrogen() outputs "H". Do not change or remove this line.
        releaseHydrogen();
        hCount++;
        if (hCount == 2 && oCount == 1) {
            hCount = 0;
            oCount = 0;
        }
        cv.notify_all();
    }

    void oxygen(std::function<void()> releaseOxygen) {
        std::unique_lock<std::mutex> lock(m);
        cv.wait(lock, [this] { return hCount == 2 && oCount == 0; });
        // releaseOxygen() outputs "O". Do not change or remove this line.
        releaseOxygen();
        oCount++;
        cv.notify_all();
    }

private:
    std::mutex m;
    std::condition_variable cv;
    int hCount;
    int oCount;
};