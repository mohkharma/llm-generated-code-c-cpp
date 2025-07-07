#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>

int findMissingNumber(const std::vector<int>& arr) {
    int n = arr.size() + 1;
    int expectedSum = n * (n + 1) / 2;
    int actualSum = std::accumulate(arr.begin(), arr.end(), 0);
    return expectedSum - actualSum;
}

void test_missing_number_at_start() {
    std::vector<int> arr = {2, 3, 4, 5, 6};
    assert(findMissingNumber(arr) == 1);
}

void test_missing_number_at_end() {
    std::vector<int> arr = {1, 2, 3, 4, 5};
    assert(findMissingNumber(arr) == 6);
}

void test_missing_number_in_middle() {
    std::vector<int> arr = {1, 2, 4, 5, 6};
    assert(findMissingNumber(arr) == 3);
}

void test_missing_number_in_large_array() {
    std::vector<int> arr;
    for (int i = 1; i <= 10000; ++i) {
        if (i != 5000) {
            arr.push_back(i);
        }
    }
    assert(findMissingNumber(arr) == 5000);
}

void test_single_missing_number() {
    std::vector<int> arr = {1};
    assert(findMissingNumber(arr) == 2);
}

void test_large_array_with_small_missing_number() {
    std::vector<int> arr;
    for (int i = 2; i <= 10000; ++i) {
        arr.push_back(i);
    }
    assert(findMissingNumber(arr) == 1);
}

void test_large_array_with_missing_number_at_middle() {
    std::vector<int> arr;
    for (int i = 1; i <= 10000; ++i) {
        if (i != 5000) {
            arr.push_back(i);
        }
    }
    assert(findMissingNumber(arr) == 5000);
}

void test_consecutive_numbers_missing_one() {
    std::vector<int> arr = {1, 2, 4, 5, 6};
    assert(findMissingNumber(arr) == 3);
}

void test_missing_number_at_end_of_small_array() {
    std::vector<int> arr = {1, 2, 3, 4};
    assert(findMissingNumber(arr) == 5);
}

void test_missing_number_at_start_of_small_array() {
    std::vector<int> arr = {2, 3, 4, 5};
    assert(findMissingNumber(arr) == 1);
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