#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// الحل كما هو
class Solution {
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        int count = 0;
        vector<long> sums(nums.size() + 1, 0);
        for (int i = 0; i < nums.size(); ++i) {
            sums[i + 1] = sums[i] + nums[i];
        }
        mergeSort(sums, 0, sums.size() - 1, lower, upper, count);
        return count;
    }

private:
    void mergeSort(vector<long>& sums, int lo, int hi, int lower, int upper, int& count) {
        if (lo >= hi) return;
        int mid = (lo + hi) / 2;
        mergeSort(sums, lo, mid, lower, upper, count);
        mergeSort(sums, mid + 1, hi, lower, upper, count);

        int i = lo, j = mid + 1, m = mid + 1, n = mid + 1;
        while (i <= mid) {
            while (m <= hi && sums[m] - sums[i] < lower) m++;
            while (n <= hi && sums[n] - sums[i] <= upper) n++;
            count += n - m;
            while (j <= hi && sums[j] < sums[i]) j++;
            i++;
        }
        inplace_merge(sums.begin() + lo, sums.begin() + mid + 1, sums.begin() + hi + 1);
    }
};

// تابع اختبار فردي
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
