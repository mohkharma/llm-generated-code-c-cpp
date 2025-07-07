#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// الكلاس كما هو
class ReversePairs {
public:
    int reversePairs(vector<int>& nums) {
        return mergeSort(nums, 0, nums.size());
    }

private:
    int mergeSort(vector<int>& nums, int start, int end) {
        if (end - start <= 1) return 0;
        int mid = (start + end) / 2;
        int count = mergeSort(nums, start, mid) + mergeSort(nums, mid, end);

        int j = mid;
        for (int i = start; i < mid; i++) {
            while (j < end && nums[i] > 2LL * nums[j]) j++;
            count += j - mid;
        }

        inplace_merge(nums.begin() + start, nums.begin() + mid, nums.begin() + end);
        return count;
    }
};

// دالة اختبار فردية
bool runTest(vector<int> input, int expected, int testId) {
    ReversePairs solution;
    int result = solution.reversePairs(input);
    if (result != expected) {
        cerr << "Test case " << testId << " failed!\n";
        cerr << "Input: ";
        for (int x : input) cerr << x << " ";
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
