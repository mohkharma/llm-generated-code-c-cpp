#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

// ------------ MountainArray مع قيود calls ------------
class MountainArray {
private:
    vector<int> arr;
    int calls;

public:
    MountainArray(vector<int> arr) : arr(arr), calls(0) {}

    int get(int index) {
        calls++;
        if (calls > 100) throw runtime_error("Too many calls");
        return arr[index];
    }

    int length() {
        return arr.size();
    }
};

// ------------------ Solution ------------------
class Solution {
public:
    int findInMountainArray(int target, MountainArray &mountainArr) {
        int peak = findPeakIndex(mountainArr);
        int index = binarySearch(mountainArr, target, 0, peak, true);
        if (index != -1) return index;
        return binarySearch(mountainArr, target, peak + 1, mountainArr.length() - 1, false);
    }

private:
    int findPeakIndex(MountainArray &arr) {
        int left = 0, right = arr.length() - 1;
        while (left < right) {
            int mid = (left + right) / 2;
            if (arr.get(mid) < arr.get(mid + 1)) left = mid + 1;
            else right = mid;
        }
        return left;
    }

    int binarySearch(MountainArray &arr, int target, int left, int right, bool ascending) {
        while (left <= right) {
            int mid = (left + right) / 2;
            int value = arr.get(mid);
            if (value == target) return mid;
            if (value < target) {
                if (ascending) left = mid + 1;
                else right = mid - 1;
            } else {
                if (ascending) right = mid - 1;
                else left = mid + 1;
            }
        }
        return -1;
    }
};

// ------------------ Test Runner ------------------
void runTest(vector<int> arr, int target, int expected, int testNum) {
    try {
        MountainArray m(arr);
        Solution s;
        int result = s.findInMountainArray(target, m);
        if (result == expected) {
            cout << "Test Case " << testNum << " Passed!" << endl;
        } else {
            cout << "Test Case " << testNum << " Failed!" << endl;
            cout << "  Expected: " << expected << ", Got: " << result << endl;
        }
    } catch (const exception &e) {
        cout << "Test Case " << testNum << " Exception: " << e.what() << endl;
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
    runTest(largeMountain, 10000, 9999, 9); // peak value
    runTest({1, 2, 3}, 2, 1, 10);

    return 0;
}
