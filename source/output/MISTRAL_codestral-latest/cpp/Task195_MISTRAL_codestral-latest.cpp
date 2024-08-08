#include <queue>

class MedianFinder {
public:
    /** initialize your data structure here. */
    MedianFinder() {}

    void addNum(int num) {
        if (small.size() == large.size()) {
            large.push(num);
            small.push(large.top());
            large.pop();
        } else {
            small.push(num);
            large.push(small.top());
            small.pop();
        }
    }

    double findMedian() {
        if (small.size() == large.size()) {
            return (small.top() + large.top()) / 2.0;
        } else {
            return small.top();
        }
    }

private:
    std::priority_queue<int> small;
    std::priority_queue<int, std::vector<int>, std::greater<int>> large;
};