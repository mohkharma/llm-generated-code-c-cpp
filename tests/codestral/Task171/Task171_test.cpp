#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// الحل كما هو
class Solution {
public:
    int reversePairs(vector<int>& nums) {
        return mergeSort(nums, 0, nums.size() - 1);
    }

private:
    int mergeSort(vector<int>& nums, int start, int end) {
        if (start >= end) return 0;
        int mid = start + (end - start) / 2;
        int count = mergeSort(nums, start, mid) + mergeSort(nums, mid + 1, end);

        int j = mid + 1;
        for (int i = start; i <= mid; i++) {
            while (j <= end && (long)nums[i] > 2 * (long)nums[j]) {
                j++;
            }
            count += j - (mid + 1);
        }

        sort(nums.begin() + start, nums.begin() + end + 1);
        return count;
    }
};

// اختبار حالة واحدة
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
