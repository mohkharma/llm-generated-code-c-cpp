#include <mutex>
#include <condition_variable>
#include <functional>
#include <thread>

class ZeroEvenOdd {
public:
  ZeroEvenOdd(int n) : n(n), count(0) {}

  void zero(std::function<void(int)> printNumber) {
    for (int i = 0; i < n; i++) {
      std::unique_lock<std::mutex> lock(m);
      cv.wait(lock, [this] { return count % 2 == 0; });
      printNumber(0);
      count++;
      if (count % 2 == 1)
        cv.notify_one();
      else
        cv.notify_all();
    }
  }

  void even(std::function<void(int)> printNumber) {
    for (int i = 2; i <= n; i += 2) {
      std::unique_lock<std::mutex> lock(m);
      cv.wait(lock, [this] { return count % 2 == 1; });
      printNumber(i);
      count++;
      if (count % 2 == 1)
        cv.notify_one();
      else
        cv.notify_all();
    }
  }

  void odd(std::function<void(int)> printNumber) {
    for (int i = 1; i <= n; i += 2) {
      std::unique_lock<std::mutex> lock(m);
      cv.wait(lock, [this] { return count % 2 == 1; });
      printNumber(i);
      count++;
      if (count % 2 == 1)
        cv.notify_one();
      else
        cv.notify_all();
    }
  }

private:
  int n;
  int count;
  std::mutex m;
  std::condition_variable cv;
};
