#include <iostream>
#include <vector>
#include <string>

template <typename T>
class Stack {
private:
    std::vector<T> items;

public:
    void push(T item) {
        items.push_back(item);
    }

    T pop() {
        if (!isEmpty()) {
            T item = items.back();
            items.pop_back();
            return item;
        }
        return T();
    }

    T peek() {
        if (!isEmpty()) {
            return items.back();
        }
        return T();
    }

    bool isEmpty() {
        return items.empty();
    }

    size_t size() {
        return items.size();
    }
};

bool test_push_multiple_elements() {
    Stack<int> stack;
    for (int i = 0; i < 1000; ++i) {
        stack.push(i);
    }
    return stack.peek() == 999;
}

bool test_pop_all_elements() {
    Stack<int> stack;
    for (int i = 0; i < 1000; ++i) {
        stack.push(i);
    }
    for (int i = 999; i >= 0; --i) {
        if (stack.pop() != i) return false;
    }
    return true;
}

bool test_peek_after_pop() {
    Stack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.pop();
    return stack.peek() == 1;
}

bool test_is_empty_after_operations() {
    Stack<int> stack;
    if (!stack.isEmpty()) return false;
    stack.push(1);
    stack.push(2);
    if (stack.isEmpty()) return false;
    stack.pop();
    stack.pop();
    return stack.isEmpty();
}

bool test_size_increment() {
    Stack<int> stack;
    if (stack.size() != 0) return false;
    stack.push(1);
    if (stack.size() != 1) return false;
    stack.push(2);
    if (stack.size() != 2) return false;
    stack.pop();
    return stack.size() == 1;
}

bool test_pop_empty_stack() {
    Stack<int> stack;
    int result = stack.pop();
    return result == 0;
}

bool test_peek_empty_stack() {
    Stack<int> stack;
    int result = stack.peek();
    return result == 0;
}

bool test_push_and_pop_large_elements() {
    Stack<std::string> stack;
    std::string large_element(10000, 'a');
    stack.push(large_element);
    if (stack.peek() != large_element) return false;
    if (stack.pop() != large_element) return false;
    return true;
}

bool test_size_with_large_operations() {
    Stack<int> stack;
    for (int i = 0; i < 10000; ++i) {
        stack.push(i);
    }
    if (stack.size() != 10000) return false;
    for (int i = 0; i < 5000; ++i) {
        stack.pop();
    }
    return stack.size() == 5000;
}

bool test_multiple_peeks() {
    Stack<int> stack;
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
    Stack<int> stack;
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
    failed += !test_push_and_pop_large_elements();
    failed += !test_size_with_large_operations();
    failed += !test_multiple_peeks();
    failed += !test_operations_on_large_stack();

    if (failed == 0) {
        std::cout << "All test cases passed!" << std::endl;
    } else {
        std::cout << failed << " test(s) failed." << std::endl;
    }

    return failed;
}
