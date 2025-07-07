#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        vector<long> prefixSum(nums.size() + 1, 0);
        for (int i = 0; i < nums.size(); i++) {
            prefixSum[i + 1] = prefixSum[i] + nums[i];
        }
        return countWhileMergeSort(prefixSum, 0, prefixSum.size() - 1, lower, upper);
    }

private:
    int countWhileMergeSort(vector<long>& prefixSum, int start, int end, int lower, int upper) {
        if (end <= start) return 0;
        int mid = start + (end - start) / 2;
        int count = countWhileMergeSort(prefixSum, start, mid, lower, upper)
                  + countWhileMergeSort(prefixSum, mid + 1, end, lower, upper);

        int j = mid + 1, k = mid + 1;
        for (int i = start; i <= mid; i++) {
            while (j <= end && prefixSum[j] - prefixSum[i] < lower) j++;
            while (k <= end && prefixSum[k] - prefixSum[i] <= upper) k++;
            count += k - j;
        }

        inplace_merge(prefixSum.begin() + start, prefixSum.begin() + mid + 1, prefixSum.begin() + end + 1);
        return count;
    }
};

bool runTest(const vector<int>& nums, int lower, int upper, int expected, int testId) {
    Solution sol;
    vector<int> input = nums;
    int result = sol.countRangeSum(input, lower, upper);
    if (result != expected) {
        cerr << "Test case " << testId << " failed!\n";
        cerr << "Input nums: ";
        for (int n : nums) cerr << n << " ";
        cerr << "\nLower: " << lower << ", Upper: " << upper;
        cerr << "\nExpected: " << expected << ", Got: " << result << "\n";
        return false;
    }
    return true;
}

int main() {
    struct TestCase {
        vector<int> nums;
        int lower;
        int upper;
        int expected;
    };

    vector<TestCase> tests = {
        {{-2, 5, -1}, -2, 2, 3},
        {{0}, 0, 0, 1},
        {{1, 2, 3, 4}, 3, 6, 5},
        {{-1, -2, -3, -4}, -6, -1, 7},
        {{3, -1, 4, -2, 5}, 0, 5, 9},
        {{0, 0, 0, 0}, 0, 0, 10},
        {{1000000, -1000000, 1000000}, -1000000, 1000000, 4},
        {{1, 2, 3, 4}, 5, 5, 1},
        {{2}, 2, 2, 1},
        {{10, 20, 30}, 100, 200, 0}
    };

    bool allPassed = true;
    for (size_t i = 0; i < tests.size(); ++i) {
        if (!runTest(tests[i].nums, tests[i].lower, tests[i].upper, tests[i].expected, i + 1)) {
            allPassed = false;
        }
    }

    if (allPassed) {
        cout << "All test cases passed successfully.\n";
    }

    return 0;
}
