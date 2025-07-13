#include <iostream>
#include <vector>

class Stack {
private:
    std::vector<int> stack;
public:
    void push(int item) {
        stack.push_back(item);
    }

    int pop() {
        if (!is_empty()) {
            int item = stack.back();
            stack.pop_back();
            return item;
        }
        return -1; // -1 when empty
    }

    int peek() {
        if (!is_empty()) {
            return stack.back();
        }
        return -1; // -1 when empty
    }

    bool is_empty() {
        return stack.empty();
    }
};

bool test_push_multiple_elements() {
    Stack stack;
    for (int i = 0; i < 1000; ++i) stack.push(i);
    return stack.peek() == 999;
}

bool test_pop_all_elements() {
    Stack stack;
    for (int i = 0; i < 1000; ++i) stack.push(i);
    for (int i = 999; i >= 0; --i) {
        if (stack.pop() != i) return false;
    }
    return true;
}

bool test_peek_after_pop() {
    Stack stack;
    stack.push(1);
    stack.push(2);
    stack.pop();
    return stack.peek() == 1;
}

bool test_is_empty_after_operations() {
    Stack stack;
    if (!stack.is_empty()) return false;
    stack.push(1);
    stack.push(2);
    if (stack.is_empty()) return false;
    stack.pop();
    stack.pop();
    return stack.is_empty();
}

bool test_size_increment() {
    Stack stack;
    int count = 0;
    if (!stack.is_empty()) return false;
    for (int i = 0; i < 10; ++i) {
        stack.push(i);
        ++count;
        if (stack.peek() != i) return false;
    }
    for (int i = 9; i >= 0; --i) {
        if (stack.pop() != i) return false;
        --count;
    }
    return stack.is_empty();
}

bool test_pop_empty_stack() {
    Stack stack;
    return stack.pop() == -1;
}

bool test_peek_empty_stack() {
    Stack stack;
    return stack.peek() == -1;
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

    if (failed == 0)
        std::cout << "All test cases passed!\n";
    else
        std::cout << failed << " test(s) failed.\n";

    return failed;
}
