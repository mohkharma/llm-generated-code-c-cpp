#include <iostream>
#include <queue>
#include <string>

class Queue {
private:
    std::queue<std::string> queue;

public:
    void enqueue(const std::string& item) {
        queue.push(item);
    }

    std::string dequeue() {
        if (queue.empty()) {
            return ""; // empty queue indicator
        }
        std::string item = queue.front();
        queue.pop();
        return item;
    }

    std::string peek() {
        if (queue.empty()) {
            return ""; // empty queue indicator
        }
        return queue.front();
    }

    bool isEmpty() {
        return queue.empty();
    }
};

bool test_enqueue_and_peek() {
    Queue queue;
    queue.enqueue("Apple");
    queue.enqueue("Banana");
    return queue.peek() == "Apple";
}

bool test_dequeue() {
    Queue queue;
    queue.enqueue("Apple");
    queue.enqueue("Banana");
    if (queue.dequeue() != "Apple") return false;
    if (queue.peek() != "Banana") return false;
    return true;
}

bool test_empty_queue() {
    Queue queue;
    if (!queue.isEmpty()) return false;
    queue.enqueue("Apple");
    if (queue.isEmpty()) return false;
    return true;
}

bool test_peek_empty_queue() {
    Queue queue;
    return queue.peek() == "";
}

bool test_dequeue_empty_queue() {
    Queue queue;
    return queue.dequeue() == "";
}

bool test_multiple_enqueue_and_dequeue() {
    Queue queue;
    queue.enqueue("Apple");
    queue.enqueue("Banana");
    queue.enqueue("Cherry");
    if (queue.dequeue() != "Apple") return false;
    if (queue.dequeue() != "Banana") return false;
    if (queue.dequeue() != "Cherry") return false;
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
