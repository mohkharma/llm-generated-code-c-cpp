#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <vector>

using namespace std;

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

vector<int> testFuncc(const string& input) {
    istringstream iss(input);
    vector<int> arr;
    int x;
    while (iss >> x) {
        arr.push_back(x);
    }
    int n = (int)arr.size();
    if (n > 0) {
        int* c_arr = new int[n];
        for (int i = 0; i < n; i++) {
            c_arr[i] = arr[i];
        }
        bubbleSort(c_arr, n);
        vector<int> sorted_arr(c_arr, c_arr + n);
        delete[] c_arr;
        return sorted_arr;
    }
    return {};
}

void assertEqual(const vector<int>& got, const vector<int>& expected, const string& testName) {
    if (got != expected) {
        cerr << "Test failed: " << testName << "\nExpected: ";
        for (int v : expected) cerr << v << " ";
        cerr << "\nGot: ";
        for (int v : got) cerr << v << " ";
        cerr << "\n";
        assert(false);
    }
}

int main() {
    assertEqual(testFuncc("4 3 2 1"), {1,2,3,4}, "test_basic");
    assertEqual(testFuncc("5"), {5}, "test_single_element");
    assertEqual(testFuncc("1 2 3 4 5"), {1,2,3,4,5}, "test_already_sorted");
    assertEqual(testFuncc("7 7 7 7"), {7,7,7,7}, "test_all_elements_same");
    assertEqual(testFuncc("-1 -3 -2 -4"), {-4,-3,-2,-1}, "test_negative_numbers");
    assertEqual(testFuncc("3 -1 0 2 -5"), {-5,-1,0,2,3}, "test_mixed_positive_and_negative");
    assertEqual(testFuncc("1000 500 2000 1500"), {500,1000,1500,2000}, "test_large_numbers");
    assertEqual(testFuncc("3 2 4 1"), {1,2,3,4}, "test_float_numbers");
    assertEqual(testFuncc("1 2 1 2 0"), {0,1,1,2,2}, "test_mixed_integers_and_floats");
    assertEqual(testFuncc(""), {}, "test_empty_input");

    cout << "All tests passed.\n";
    return 0;
}
