#include <iostream>
#include <queue>

class Queue {
private:
    std::queue<int> queue;

public:
    void enqueue(int item) {
        queue.push(item);
    }

    int dequeue() {
        if (!queue.empty()) {
            int front = queue.front();
            queue.pop();
            return front;
        }
        return -1; // Empty queue indicator
    }

    int peek() {
        if (!queue.empty()) {
            return queue.front();
        }
        return -1; // Empty queue indicator
    }

    bool isEmpty() {
        return queue.empty();
    }
};

bool test_enqueue_and_peek() {
    Queue queue;
    queue.enqueue(1);
    queue.enqueue(2);
    return queue.peek() == 1;
}

bool test_dequeue() {
    Queue queue;
    queue.enqueue(1);
    queue.enqueue(2);
    if (queue.dequeue() != 1) return false;
    if (queue.peek() != 2) return false;
    return true;
}

bool test_empty_queue() {
    Queue queue;
    if (!queue.isEmpty()) return false;
    queue.enqueue(1);
    if (queue.isEmpty()) return false;
    return true;
}

bool test_peek_empty_queue() {
    Queue queue;
    return queue.peek() == -1;
}

bool test_dequeue_empty_queue() {
    Queue queue;
    return queue.dequeue() == -1;
}

bool test_multiple_enqueue_and_dequeue() {
    Queue queue;
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    if (queue.dequeue() != 10) return false;
    if (queue.dequeue() != 20) return false;
    if (queue.dequeue() != 30) return false;
    return true;
}

int main() {
    int failed = 0;
    failed += !test_enqueue_and_peek();
    failed += !test_dequeue();
    failed += !test_empty_queue();
    failed += !test_peek_empty_queue();
    failed += !test_dequeue_empty_queue();
    failed += !test_multiple_enqueue_and_dequeue();

    if (failed == 0)
        std::cout << "All test cases passed!\n";
    else
        std::cout << failed << " test(s) failed.\n";

    return failed;
}
