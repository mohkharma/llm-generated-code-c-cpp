#include <iostream>
#include <cassert>
using namespace std;

int findMissingNumber(int arr[], int n) {
    int total_sum = n * (n + 1) / 2;
    int array_sum = 0;
    for (int i = 0; i < n-1; i++) {
        array_sum += arr[i];
    }
    return total_sum - array_sum;
}

void test_missing_number_at_start() {
    int arr[] = {2, 3, 4, 5, 6};
    int n = 6;
    assert(findMissingNumber(arr, n) == 1);
}

void test_missing_number_at_end() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = 6;
    assert(findMissingNumber(arr, n) == 6);
}

void test_missing_number_in_middle() {
    int arr[] = {1, 2, 4, 5, 6};
    int n = 6;
    assert(findMissingNumber(arr, n) == 3);
}

void test_missing_number_in_large_array() {
    int* arr = new int[9999];
    int idx = 0;
    for (int i = 1; i <= 10000; ++i) {
        if (i != 5000) {
            arr[idx++] = i;
        }
    }
    assert(findMissingNumber(arr, 10000) == 5000);
    delete[] arr;
}

void test_single_missing_number() {
    int arr[] = {1};
    int n = 2;
    assert(findMissingNumber(arr, n) == 2);
}

void test_large_array_with_small_missing_number() {
    int* arr = new int[9999];
    int idx = 0;
    for (int i = 2; i <= 10000; ++i) {
        arr[idx++] = i;
    }
    assert(findMissingNumber(arr, 10000) == 1);
    delete[] arr;
}

void test_large_array_with_missing_number_at_middle() {
    int* arr = new int[9999];
    int idx = 0;
    for (int i = 1; i <= 10000; ++i) {
        if (i != 5000) {
            arr[idx++] = i;
        }
    }
    assert(findMissingNumber(arr, 10000) == 5000);
    delete[] arr;
}

void test_consecutive_numbers_missing_one() {
    int arr[] = {1, 2, 4, 5, 6};
    int n = 6;
    assert(findMissingNumber(arr, n) == 3);
}

void test_missing_number_at_end_of_small_array() {
    int arr[] = {1, 2, 3, 4};
    int n = 5;
    assert(findMissingNumber(arr, n) == 5);
}

void test_missing_number_at_start_of_small_array() {
    int arr[] = {2, 3, 4, 5};
    int n = 5;
    assert(findMissingNumber(arr, n) == 1);
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

    cout << "All tests passed!" << endl;
    return 0;
}