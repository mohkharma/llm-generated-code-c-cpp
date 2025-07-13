#include <iostream>
#include <vector>
using namespace std;

// الحل brute-force كما هو
class Solution {
public:
    int reversePairs(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return 0;
        int count = 0;
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                if ((long long)nums[i] > 2LL * nums[j]) {
                    count++;
                }
            }
        }
        return count;
    }
};

// اختبار فردي
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
