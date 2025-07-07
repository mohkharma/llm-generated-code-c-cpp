#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// الحل كما هو (rangeSum)
class Solution {
public:
    int rangeSum(vector<int>& nums, int lower, int upper) {
        int n = nums.size();
        vector<int> preSum(n);
        preSum[0] = nums[0];
        for (int i = 1; i < n; i++) {
            preSum[i] = preSum[i - 1] + nums[i];
        }

        int ans = 0;
        for (int i = 0; i < n; i++) {
            int lo = i;
            int hi = n - 1;
            int idx = -1;
            while (lo <= hi) {
                int mid = (lo + hi) / 2;
                int cur = preSum[mid];
                if (i > 0) cur -= preSum[i - 1];
                if (cur < lower) {
                    lo = mid + 1;
                } else {
                    idx = mid;
                    hi = mid - 1;
                }
            }
            if (idx != -1) {
                int cur = preSum[idx];
                if (i > 0) cur -= preSum[i - 1];
                if (lower <= cur && cur <= upper) {
                    ans++;
                }
            }
        }
        return ans;
    }
};

// تابع اختبار فردي
bool runTest(const vector<int>& nums, int lower, int upper, int expected, int testId) {
    Solution sol;
    vector<int> input = nums;
    int result = sol.rangeSum(input, lower, upper);
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

// البرنامج الرئيسي
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
