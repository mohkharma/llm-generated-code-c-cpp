#include <iostream>

struct Node {
    int data;
    Node* next;
};

class Queue {
public:
    Node* front;
    Node* rear;

    Queue() {
        front = rear = nullptr;
    }

    void enqueue(int x) {
        Node* temp = new Node;
        temp->data = x;
        temp->next = nullptr;
        if (rear == nullptr) {
            front = rear = temp;
            return;
        }
        rear->next = temp;
        rear = temp;
    }

    void dequeue() {
        if (front == nullptr)
            return;
        Node* temp = front;
        front = front->next;
        if (front == nullptr)
            rear = nullptr;
        delete temp;
    }

    int peek() {
        if (front == nullptr) {
            return -1;  // Return -1 if empty
        }
        return front->data;
    }

    bool isEmpty() {
        return front == nullptr;
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
    queue.dequeue();
    return queue.peek() == 2;
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
    queue.dequeue();
    return queue.peek() == -1;
}

bool test_multiple_enqueue_and_dequeue() {
    Queue queue;
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    queue.dequeue();
    if (queue.peek() != 20) return false;
    queue.dequeue();
    if (queue.peek() != 30) return false;
    queue.dequeue();
    return queue.peek() == -1;
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
