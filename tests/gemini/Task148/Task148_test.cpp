#include <iostream>
#include <vector>
#include <stdexcept>

template <typename T>
class Stack {
private:
    std::vector<T> items;

public:
    void push(T item) {
        items.push_back(item);
    }

    T pop() {
        if (!is_empty()) {
            T item = items.back();
            items.pop_back();
            return item;
        } else {
            throw std::runtime_error("Stack is empty");
        }
    }

    T peek() {
        if (!is_empty()) {
            return items.back();
        } else {
            throw std::runtime_error("Stack is empty");
        }
    }

    bool is_empty() {
        return items.empty();
    }
};

bool test_push_pop_peek() {
    Stack<int> stack;
    stack.push(10);
    stack.push(20);
    if (stack.peek() != 20) return false;
    if (stack.pop() != 20) return false;
    if (stack.peek() != 10) return false;
    if (stack.pop() != 10) return false;
    return stack.is_empty();
}

bool test_pop_empty() {
    Stack<int> stack;
    try {
        stack.pop();
        return false;
    } catch (std::runtime_error& e) {
        return std::string(e.what()) == "Stack is empty";
    }
}

bool test_peek_empty() {
    Stack<int> stack;
    try {
        stack.peek();
        return false;
    } catch (std::runtime_error& e) {
        return std::string(e.what()) == "Stack is empty";
    }
}

int main() {
    int failed = 0;
    failed += !test_push_pop_peek();
    failed += !test_pop_empty();
    failed += !test_peek_empty();

    if (failed == 0) {
        std::cout << "All tests passed.\n";
    } else {
        std::cout << failed << " test(s) failed.\n";
    }
    return failed;
}
