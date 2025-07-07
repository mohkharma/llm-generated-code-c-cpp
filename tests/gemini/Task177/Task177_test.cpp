// Task177_Test.cpp

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "../../../source/output/gemini/cpp/Task177_GEMINI_gemini-1.5-pro-001.cpp"

int main() {
    Solution solution;

    struct TestCase {
        vector<int> nums;
        int k;
        int expected;
        string description;
    };

    vector<TestCase> tests = {
        {{10, 2, -10, 5, 20}, 2, 37, "Test case 1"},
        {{-1, -2, -3}, 1, -1, "Test case 2"},
        {{10, -2, -10, -5, 20}, 2, 23, "Test case 3"},
        {{1, 2, 3, 4, 5}, 2, 15, "Test case 4"},
        {{-1, 0, 1}, 2, 1, "Test case 5"},
        {{1, -1, 2, 3, -2}, 2, 6, "Test case 6"},
        {{5, -1, 3, -2, 4, -1}, 3, 12, "Test case 7"},
        {{2, 1, -2, 3, -4}, 1, 6, "Test case 8"},
        {{10, -2, 3, -4, 5}, 4, 18, "Test case 9"},
        {{1, -2, 3, 10, -1}, 2, 14, "Test case 10"}
    };

    bool all_passed = true;

    for (int i = 0; i < tests.size(); ++i) {
        vector<int> input = tests[i].nums; // avoid mutation
        int result = solution.constrainedSubsetSum(input, tests[i].k);
        if (result != tests[i].expected) {
            all_passed = false;
            cout << tests[i].description << " FAILED!\n";
            cout << "  Input: nums = [";
            for (int j = 0; j < tests[i].nums.size(); ++j) {
                if (j > 0) cout << ", ";
                cout << tests[i].nums[j];
            }
            cout << "], k = " << tests[i].k << endl;
            cout << "  Expected: " << tests[i].expected << endl;
            cout << "  Got:      " << result << endl;
        }
    }

    if (all_passed) {
        cout << "✅ All test cases passed!" << endl;
    }

    return 0;
}
