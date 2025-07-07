#include <iostream>
#include <vector>
#include <cassert>

int findMissing(std::vector<int>& arr) {
    int n = arr.size() + 1;
    int total = n * (n + 1) / 2;
    int sum = 0;
    for (int i : arr) {
        sum += i;
    }
    return total - sum;
}

void test_missing_number_at_start() {
    std::vector<int> arr = {2, 3, 4, 5, 6};
    assert(findMissing(arr) == 1);
}

void test_missing_number_at_end() {
    std::vector<int> arr = {1, 2, 3, 4, 5};
    assert(findMissing(arr) == 6);
}

void test_missing_number_in_middle() {
    std::vector<int> arr = {1, 2, 4, 5, 6};
    assert(findMissing(arr) == 3);
}

void test_missing_number_in_large_array() {
    std::vector<int> arr;
    for (int i = 1; i <= 10000; ++i) {
        if (i != 5000) {
            arr.push_back(i);
        }
    }
    assert(findMissing(arr) == 5000);
}

void test_single_missing_number() {
    std::vector<int> arr = {1};
    assert(findMissing(arr) == 2);
}

void test_large_array_with_small_missing_number() {
    std::vector<int> arr;
    for (int i = 2; i <= 10000; ++i) {
        arr.push_back(i);
    }
    assert(findMissing(arr) == 1);
}

void test_large_array_with_missing_number_at_middle() {
    std::vector<int> arr;
    for (int i = 1; i <= 10000; ++i) {
        if (i != 5000) {
            arr.push_back(i);
        }
    }
    assert(findMissing(arr) == 5000);
}

void test_consecutive_numbers_missing_one() {
    std::vector<int> arr = {1, 2, 4, 5, 6};
    assert(findMissing(arr) == 3);
}

void test_missing_number_at_end_of_small_array() {
    std::vector<int> arr = {1, 2, 3, 4};
    assert(findMissing(arr) == 5);
}

void test_missing_number_at_start_of_small_array() {
    std::vector<int> arr = {2, 3, 4, 5};
    assert(findMissing(arr) == 1);
}

int main() {
    test_missing_number_at_start();
    test_missing_number_at_end();
    test_missing_number_in_middle();
    test_missing_number_in_large_array();
    test_single_missing_number();
    test_large_array_with_small_missing_number();
    test_large_array_with_missing_number_at_middle();
    test_consecutive_numbers_missing_one();
    test_missing_number_at_end_of_small_array();
    test_missing_number_at_start_of_small_array();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}