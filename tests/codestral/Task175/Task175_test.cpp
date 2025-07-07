#include <iostream>
#include <vector>
#include <string>
#include <exception>
#include <sstream>
#include <stdexcept>
using namespace std;

// ---------------- Provided Classes ----------------

class MountainArray {
private:
    std::vector<int> arr;
    int calls;

public:
    MountainArray(std::vector<int> arr) : arr(arr), calls(0) {}

    int get(int index) {
        calls++;
        if (calls > 100)
            throw std::runtime_error("Too many calls");
        return arr[index];
    }

    int length() {
        return arr.size();
    }

    int getCallCount() const {
        return calls;
    }
};

class Solution {
public:
    int findInMountainArray(int target, MountainArray &mountainArr) {
        int peak = findPeak(mountainArr);
        int left = binarySearch(mountainArr, target, 0, peak, true);
        if (left != -1) return left;
        return binarySearch(mountainArr, target, peak + 1, mountainArr.length() - 1, false);
    }

private:
    int findPeak(MountainArray &mountainArr) {
        int left = 0, right = mountainArr.length() - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (mountainArr.get(mid) < mountainArr.get(mid + 1)) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return left;
    }

    int binarySearch(MountainArray &mountainArr, int target, int left, int right, bool isAscending) {
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int val = mountainArr.get(mid);
            if (val == target) return mid;
            if (val < target) {
                if (isAscending) left = mid + 1;
                else right = mid - 1;
            } else {
                if (isAscending) right = mid - 1;
                else left = mid + 1;
            }
        }
        return -1;
    }
};

// ----------------- Test Harness -------------------

void runTest(const vector<int>& array, int target, int expected, int testCaseNumber) {
    try {
        MountainArray m(array);
        Solution s;
        int result = s.findInMountainArray(target, m);

        if (result == expected) {
            cout << "Test Case " << testCaseNumber << " Passed!" << endl;
        } else {
            cout << "Test Case " << testCaseNumber << " Failed!" << endl;
            cout << "  Expected: " << expected << ", Got: " << result << endl;
        }
    } catch (std::exception& e) {
        cout << "Test Case " << testCaseNumber << " Failed with exception: " << e.what() << endl;
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
    runTest(largeMountain, 10000, 9999, 9); // Peak value

    runTest({1, 2, 3}, 2, 1, 10);

    return 0;
}
