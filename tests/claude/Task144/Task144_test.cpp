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

vector<int> mergeSortedArrays(const vector<int>& arr1, const vector<int>& arr2) {
    // إنشاء نسخ من المصفوفات لفرزها
    vector<int> sorted1 = arr1;
    vector<int> sorted2 = arr2;

    sort(sorted1.begin(), sorted1.end());
    sort(sorted2.begin(), sorted2.end());

    vector<int> merged;
    size_t i = 0, j = 0;
    while (i < sorted1.size() && j < sorted2.size()) {
        if (sorted1[i] <= sorted2[j]) {
            merged.push_back(sorted1[i]);
            i++;
        } else {
            merged.push_back(sorted2[j]);
            j++;
        }
    }
    merged.insert(merged.end(), sorted1.begin() + i, sorted1.end());
    merged.insert(merged.end(), sorted2.begin() + j, sorted2.end());
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
    assertEqual(mergeSortedArrays(parseArray(""), parseArray("")), {}, "test_empty_arrays");
    assertEqual(mergeSortedArrays(parseArray(""), parseArray("1 3 5")), {1,3,5}, "test_one_empty_array_1");
    assertEqual(mergeSortedArrays(parseArray("2 4 6"), parseArray("")), {2,4,6}, "test_one_empty_array_2");
    assertEqual(mergeSortedArrays(parseArray("1"), parseArray("1")), {1,1}, "test_single_element_arrays_1");
    assertEqual(mergeSortedArrays(parseArray("1"), parseArray("2")), {1,2}, "test_single_element_arrays_2");
    assertEqual(mergeSortedArrays(parseArray("1 2 3"), parseArray("4 5 6")), {1,2,3,4,5,6}, "test_different_sizes_with_all_smaller_elements");
    assertEqual(mergeSortedArrays(parseArray("1 3 5"), parseArray("2 3 4")), {1,2,3,3,4,5}, "test_some_overlapping_elements");
    assertEqual(mergeSortedArrays(parseArray("2 2 2"), parseArray("2 2 2")), {2,2,2,2,2,2}, "test_all_elements_same");
    assertEqual(mergeSortedArrays(parseArray("1 3 5 7"), parseArray("2 4 6 8")), {1,2,3,4,5,6,7,8}, "test_interleaving_elements");
    assertEqual(mergeSortedArrays(parseArray("1 2"), parseArray("1000 2000 3000")), {1,2,1000,2000,3000}, "test_large_element_diff");
    assertEqual(mergeSortedArrays(parseArray("9 7 5"), parseArray("8 6 4")), {4,5,6,7,8,9}, "test_reverse_order_arrays");

    cout << "All tests passed.\n";
    return 0;
}
