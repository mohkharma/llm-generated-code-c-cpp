#include <iostream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

class MountainArray {
    vector<int> arr;
public:
    MountainArray(const vector<int>& input) : arr(input) {}

    int get(int index) {
        return arr[index];
    }

    int length() {
        return arr.size();
    }
};

class Solution {
public:
    int findInMountainArray(int target, MountainArray &mountainArr) {
        int length = mountainArr.length();

        // Find peak element
        int left = 0, right = length - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (mountainArr.get(mid) < mountainArr.get(mid + 1)) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        int peak = left;

        // Binary search in the left side
        left = 0;
        right = peak;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int midVal = mountainArr.get(mid);
            if (midVal == target) {
                return mid;
            } else if (midVal < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        // Binary search in the right side
        left = peak;
        right = length - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int midVal = mountainArr.get(mid);
            if (midVal == target) {
                return mid;
            } else if (midVal > target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return -1;
    }
};

void runTest(const vector<int>& array, int target, int expected, int testCaseNumber) {
    MountainArray m(array);
    Solution s;
    int result = s.findInMountainArray(target, m);

    if (result == expected) {
        cout << "Test Case " << testCaseNumber << " Passed!" << endl;
    } else {
        cout << "Test Case " << testCaseNumber << " Failed!" << endl;
        cout << "  Input array: [";
        for (size_t i = 0; i < array.size(); ++i) {
            if (i > 0) cout << ",";
            cout << array[i];
        }
        cout << "], target: " << target << endl;
        cout << "  Expected: " << expected << ", Got: " << result << endl;
    }
}

int main() {
    runTest({1, 2, 3, 4, 5, 3, 1}, 3, 2, 1);
    runTest({1, 2, 3, 4, 5, 3, 1}, 1, 0, 2);
    runTest({0, 1, 2, 4, 2, 1}, 3, -1, 3);
    runTest({1, 3, 5, 7, 6, 4, 2}, 7, 3, 4);
    runTest({5, 4, 3, 2, 1, 0}, 5, 0, 5);
    runTest({1, 2, 3, 4, 3, 2, 1}, 1, 0, 6);

    vector<int> largeMountain;
    for (int i = 1; i <= 10000; ++i) largeMountain.push_back(i);
    for (int i = 9999; i >= 1; --i) largeMountain.push_back(i);
    runTest(largeMountain, 5000, 4999, 7);
    runTest(largeMountain, 9998, 9997, 8);
    runTest(largeMountain, 10000, 9999, 9); // Expected: 9999 because 10000 is the peak
    runTest({1, 2, 3}, 2, 1, 10);

    return 0;
}
