#include <iostream>
#include <vector>
using namespace std;

// --------- MountainArray و Solution من كودك ---------
class MountainArray {
public:
    std::vector<int> array;
    MountainArray(std::vector<int>& arr) : array(arr) {}

    int get(int index) {
        return array[index];
    }

    int length() {
        return array.size();
    }
};

class Solution {
public:
    int findInMountainArray(int target, MountainArray &mountainArr) {
        int n = mountainArr.length();
        int left = 0, right = n - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (mountainArr.get(mid) < mountainArr.get(mid + 1)) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        int peak = left;
        left = 0;
        right = peak;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (mountainArr.get(mid) == target) {
                return mid;
            } else if (mountainArr.get(mid) < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        left = peak;
        right = n - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (mountainArr.get(mid) == target) {
                return mid;
            } else if (mountainArr.get(mid) > target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return -1;
    }
};

// ----------------- Test Runner -------------------
void runTest(vector<int> arr, int target, int expected, int testNum) {
    MountainArray m(arr);
    Solution s;
    int result = s.findInMountainArray(target, m);
    if (result == expected) {
        cout << "Test Case " << testNum << " Passed!" << endl;
    } else {
        cout << "Test Case " << testNum << " Failed!" << endl;
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
    runTest(largeMountain, 10000, 9999, 9); // 10000 is at peak
    runTest({1, 2, 3}, 2, 1, 10);

    return 0;
}
