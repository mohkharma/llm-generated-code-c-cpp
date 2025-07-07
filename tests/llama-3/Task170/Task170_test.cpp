#include <iostream>
#include <vector>
using namespace std;

// الحل: brute-force باستخدام prefix sums
class Solution {
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        int n = nums.size();
        vector<long long> sums(n + 1);
        for (int i = 0; i < n; i++) {
            sums[i + 1] = sums[i] + nums[i];
        }

        int res = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                long long rangeSum = sums[j + 1] - sums[i];
                if (lower <= rangeSum && rangeSum <= upper) {
                    res++;
                }
            }
        }
        return res;
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
