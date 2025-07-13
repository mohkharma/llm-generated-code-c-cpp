#include <iostream>
#include <stack>
#include <stdexcept>

class MyStack {
private:
    std::stack<int> stack;

public:
    void push(int item) {
        stack.push(item);
    }

    int pop() {
        if (stack.empty()) {
            throw std::runtime_error("Stack is empty");
        }
        int item = stack.top();
        stack.pop();
        return item;
    }

    int peek() {
        if (stack.empty()) {
            throw std::runtime_error("Stack is empty");
        }
        return stack.top();
    }

    bool isEmpty() const {
        return stack.empty();
    }

    size_t size() const {
        return stack.size();
    }
};

bool test_push_multiple_elements() {
    MyStack stack;
    for (int i = 0; i < 1000; ++i) {
        stack.push(i);
    }
    return stack.peek() == 999;
}

bool test_pop_all_elements() {
    MyStack stack;
    for (int i = 0; i < 1000; ++i) {
        stack.push(i);
    }
    for (int i = 999; i >= 0; --i) {
        if (stack.pop() != i) return false;
    }
    return true;
}

bool test_peek_after_pop() {
    MyStack stack;
    stack.push(1);
    stack.push(2);
    stack.pop();
    return stack.peek() == 1;
}

bool test_is_empty_after_operations() {
    MyStack stack;
    if (!stack.isEmpty()) return false;
    stack.push(1);
    stack.push(2);
    if (stack.isEmpty()) return false;
    stack.pop();
    stack.pop();
    return stack.isEmpty();
}

bool test_size_increment() {
    MyStack stack;
    if (stack.size() != 0) return false;
    stack.push(1);
    if (stack.size() != 1) return false;
    stack.push(2);
    if (stack.size() != 2) return false;
    stack.pop();
    return stack.size() == 1;
}

bool test_pop_empty_stack() {
    MyStack stack;
    try {
        stack.pop();
        return false; // should not reach here
    } catch (const std::runtime_error& e) {
        return std::string(e.what()) == "Stack is empty";
    }
}

bool test_peek_empty_stack() {
    MyStack stack;
    try {
        stack.peek();
        return false; // should not reach here
    } catch (const std::runtime_error& e) {
        return std::string(e.what()) == "Stack is empty";
    }
}

bool test_multiple_peeks() {
    MyStack stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    if (stack.peek() != 3) return false;
    stack.pop();
    if (stack.peek() != 2) return false;
    stack.pop();
    return stack.peek() == 1;
}

bool test_operations_on_large_stack() {
    MyStack stack;
    for (int i = 0; i < 10000; ++i) {
        stack.push(i);
    }
    for (int i = 0; i < 5000; ++i) {
        stack.pop();
    }
    return stack.peek() == 4999;
}

int main() {
    int failed = 0;
    failed += !test_push_multiple_elements();
    failed += !test_pop_all_elements();
    failed += !test_peek_after_pop();
    failed += !test_is_empty_after_operations();
    failed += !test_size_increment();
    failed += !test_pop_empty_stack();
    failed += !test_peek_empty_stack();
    failed += !test_multiple_peeks();
    failed += !test_operations_on_large_stack();

    if (failed == 0) {
        std::cout << "All test cases passed!" << std::endl;
    } else {
        std::cout << failed << " test(s) failed." << std::endl;
    }
    return failed;
}

