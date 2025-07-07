#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

using namespace std;

vector<int> parseArray(const string& input) {
    istringstream iss(input);
    vector<int> arr;
    int x;
    while (iss >> x) {
        arr.push_back(x);
    }
    return arr;
}

vector<int> mergeArrays(const vector<int>& arr1, const vector<int>& arr2) {
    vector<int> merged(arr1.size() + arr2.size());
    for (size_t i = 0; i < arr1.size(); ++i) {
        merged[i] = arr1[i];
    }
    for (size_t i = 0; i < arr2.size(); ++i) {
        merged[arr1.size() + i] = arr2[i];
    }
    sort(merged.begin(), merged.end());
    return merged;
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
    assertEqual(mergeArrays(parseArray(""), parseArray("")), {}, "test_empty_arrays");
    assertEqual(mergeArrays(parseArray(""), parseArray("1 3 5")), {1,3,5}, "test_one_empty_array_1");
    assertEqual(mergeArrays(parseArray("2 4 6"), parseArray("")), {2,4,6}, "test_one_empty_array_2");
    assertEqual(mergeArrays(parseArray("1"), parseArray("1")), {1,1}, "test_single_element_arrays_1");
    assertEqual(mergeArrays(parseArray("1"), parseArray("2")), {1,2}, "test_single_element_arrays_2");
    assertEqual(mergeArrays(parseArray("1 2 3"), parseArray("4 5 6")), {1,2,3,4,5,6}, "test_different_sizes_with_all_smaller_elements");
    assertEqual(mergeArrays(parseArray("1 3 5"), parseArray("2 3 4")), {1,2,3,3,4,5}, "test_some_overlapping_elements");
    assertEqual(mergeArrays(parseArray("2 2 2"), parseArray("2 2 2")), {2,2,2,2,2,2}, "test_all_elements_same");
    assertEqual(mergeArrays(parseArray("1 3 5 7"), parseArray("2 4 6 8")), {1,2,3,4,5,6,7,8}, "test_interleaving_elements");
    assertEqual(mergeArrays(parseArray("1 2"), parseArray("1000 2000 3000")), {1,2,1000,2000,3000}, "test_large_element_diff");
    assertEqual(mergeArrays(parseArray("9 7 5"), parseArray("8 6 4")), {4,5,6,7,8,9}, "test_reverse_order_arrays");

    cout << "All tests passed.\n";
    return 0;
}
