#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int reversePairs(vector<int>& nums) {
        return mergeSort(nums, 0, nums.size() - 1);
    }

private:
    int mergeSort(vector<int>& nums, int left, int right) {
        if (left >= right) return 0;
        int mid = left + (right - left) / 2;
        int count = mergeSort(nums, left, mid) + mergeSort(nums, mid + 1, right);

        int j = mid + 1;
        for (int i = left; i <= mid; i++) {
            while (j <= right && nums[i] > 2LL * nums[j]) {
                j++;
            }
            count += j - (mid + 1);
        }

        merge(nums, left, mid, right);
        return count;
    }

    void merge(vector<int>& nums, int left, int mid, int right) {
        vector<int> temp(right - left + 1);
        int i = left, j = mid + 1, k = 0;

        while (i <= mid && j <= right) {
            if (nums[i] <= nums[j]) {
                temp[k++] = nums[i++];
            } else {
                temp[k++] = nums[j++];
            }
        }

        while (i <= mid) temp[k++] = nums[i++];
        while (j <= right) temp[k++] = nums[j++];

        for (int p = 0; p < temp.size(); p++) {
            nums[left + p] = temp[p];
        }
    }
};

bool runTest(vector<int> input, int expected, int testId) {
    Solution sol;
    int result = sol.reversePairs(input);
    if (result != expected) {
        cerr << "Test case " << testId << " failed.\n";
        cerr << "Input: ";
        for (int n : input) cerr << n << " ";
        cerr << "\nExpected: " << expected << ", Got: " << result << "\n";
        return false;
    }
    return true;
}

int main() {
    vector<pair<vector<int>, int>> tests = {
        {{1, 3, 2, 3, 1}, 2},
        {{2, 4, 3, 5, 1}, 3},
        {{1, 2, 3, 4, 5}, 0},
        {{5, 4, 3, 2, 1}, 6},
        {{1, 5, 2, 6, 3}, 2},
        {{1}, 0},
        {{3, 1, 4, 2, 5}, 1},
        {{10, 5, 3, 2, 1}, 6},
        {{4, 2, 6, 1, 3}, 3},
        {{7, 5, 8, 2, 4}, 3}
    };

    bool allPassed = true;
    for (int i = 0; i < tests.size(); ++i) {
        if (!runTest(tests[i].first, tests[i].second, i + 1)) {
            allPassed = false;
        }
    }

    if (allPassed) {
        cout << "All test cases passed successfully.\n";
    }

    return 0;
}
