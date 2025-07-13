// Task170_Test.cpp
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>

class Solution {
public:
    int countRangeSum(std::vector<int>& nums, int lower, int upper) {
        std::vector<long long> prefixSum(nums.size() + 1, 0);
        for (int i = 0; i < nums.size(); i++) {
            prefixSum[i + 1] = prefixSum[i] + nums[i];
        }
        return mergeSort(prefixSum, 0, prefixSum.size() - 1, lower, upper);
    }

private:
    int mergeSort(std::vector<long long>& arr, int left, int right, int lower, int upper) {
        if (left >= right) return 0;
        int mid = (left + right) / 2;
        int count = mergeSort(arr, left, mid, lower, upper)
                  + mergeSort(arr, mid + 1, right, lower, upper);
        int j = mid + 1, k = mid + 1;
        for (int i = left; i <= mid; i++) {
            while (j <= right && arr[j] - arr[i] < lower) j++;
            while (k <= right && arr[k] - arr[i] <= upper) k++;
            count += k - j;
        }
        std::inplace_merge(arr.begin() + left, arr.begin() + mid + 1, arr.begin() + right + 1);
        return count;
    }
};

bool runTest(const std::vector<int>& nums, int lower, int upper, int expected, int testId) {
    Solution sol;
    std::vector<int> input = nums;
    int result = sol.countRangeSum(input, lower, upper);
    if (result != expected) {
        std::cerr << "Test case " << testId << " failed!\n";
        std::cerr << "Input nums: ";
        for (int n : nums) std::cerr << n << " ";
        std::cerr << "\nLower: " << lower << ", Upper: " << upper;
        std::cerr << "\nExpected: " << expected << ", Got: " << result << "\n";
        return false;
    }
    return true;
}

int main() {
    struct TestCase {
        std::vector<int> nums;
        int lower;
        int upper;
        int expected;
    };

    std::vector<TestCase> tests = {
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
        const auto& t = tests[i];
        if (!runTest(t.nums, t.lower, t.upper, t.expected, i + 1)) {
            allPassed = false;
        }
    }

    if (allPassed) {
        std::cout << "All test cases passed successfully.\n";
    }

    return 0;
}
