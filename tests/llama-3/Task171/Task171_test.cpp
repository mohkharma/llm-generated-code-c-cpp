#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// الحل المعطى كما هو
class Solution {
public:
    int reversePairs(vector<int>& nums) {
        return mergeSort(nums, 0, nums.size() - 1);
    }

private:
    int mergeSort(vector<int>& nums, int left, int right) {
        if (left >= right) {
            return 0;
        }
        int mid = left + (right - left) / 2;
        int left_count = mergeSort(nums, left, mid);
        int right_count = mergeSort(nums, mid + 1, right);
        int merged_count = merge(nums, left, mid, right);
        return left_count + right_count + merged_count;
    }

    int merge(vector<int>& nums, int left, int mid, int right) {
        vector<int> temp(right - left + 1);
        int left_index = left, right_index = mid + 1, temp_index = 0, count = 0;

        // Count reverse pairs (بمنطق خاطئ كما هو)
        while (left_index <= mid && right_index <= right) {
            if (nums[left_index] <= 2 * nums[right_index]) {
                temp[temp_index++] = nums[left_index++];
            } else {
                temp[temp_index++] = nums[right_index++];
                count += mid - left_index + 1;
            }
        }

        while (left_index <= mid) temp[temp_index++] = nums[left_index++];
        while (right_index <= right) temp[temp_index++] = nums[right_index++];
        copy(temp.begin(), temp.end(), nums.begin() + left);
        return count;
    }
};

// دالة اختبار لحالة واحدة
bool runTest(vector<int> input, int expected, int testId) {
    Solution sol;
    int result = sol.reversePairs(input);
    if (result != expected) {
        cerr << "Test case " << testId << " failed!\n";
        cerr << "Input: ";
        for (int x : input) cerr << x << " ";
        cerr << "\nExpected: " << expected << ", Got: " << result << "\n";
        return false;
    }
    return true;
}

// البرنامج الرئيسي
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
