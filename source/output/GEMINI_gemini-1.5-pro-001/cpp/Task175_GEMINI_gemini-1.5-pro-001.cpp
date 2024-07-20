#include <vector>

using namespace std;

class MountainArray {
public:
    vector<int> array;

    MountainArray(vector<int>& arr) : array(arr) {}

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
            int mid = (left + right) / 2;
            if (mountainArr.get(mid) < mountainArr.get(mid + 1)) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        int peak = left;
        int index = binarySearch(mountainArr, target, 0, peak, true);
        if (index != -1) {
            return index;
        }
        return binarySearch(mountainArr, target, peak + 1, n - 1, false);
    }

private:
    int binarySearch(MountainArray &mountainArr, int target, int left, int right, bool ascending) {
        while (left <= right) {
            int mid = (left + right) / 2;
            int midVal = mountainArr.get(mid);
            if (midVal == target) {
                return mid;
            } else if ((midVal < target && ascending) || (midVal > target && !ascending)) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return -1;
    }
};

int main() {
    Solution solution;
    vector<int> arr = {1, 2, 3, 4, 5, 3, 1};
    MountainArray mountainArr(arr);
    int target = 3;
    int result = solution.findInMountainArray(target, mountainArr);
    // Output: 2
    return 0;
}