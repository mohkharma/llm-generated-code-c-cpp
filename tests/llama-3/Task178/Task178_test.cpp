// Task178_Test.cpp

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "../../../source/output/llama-3/cpp/Task178_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"

int main() {
    Solution sol;

    struct TestCase {
        vector<int> nums;
        int k;
        int expected;
        string description;
    };

    vector<TestCase> tests = {
        {{1}, 1, 1, "Test case 1"},
        {{1, 2}, 4, -1, "Test case 2"},
        {{2, -1, 2}, 3, 3, "Test case 3"},
        {{1, 2, 3, 4, 5}, 11, 3, "Test case 4"},
        {{1, 2, 3, 4, 5}, 15, 5, "Test case 5"},
        {{10, -5, 10}, 10, 1, "Test case 6"},
        {{-1, -1, -1, -1, 5}, 5, 1, "Test case 7"},
        {{1, -2, 3, 4, 5}, 7, 2, "Test case 8"},
        {{100, -50, 50, 50, 50}, 150, 3, "Test case 9"},
        {{5, -10, 7, -2, 15}, 15, 1, "Test case 10"}
    };

    bool all_passed = true;

    for (int i = 0; i < tests.size(); ++i) {
        vector<int> input = tests[i].nums;
        int result = sol.shortestSubarray(input, tests[i].k);
        if (result != tests[i].expected) {
            all_passed = false;
            cout << tests[i].description << " FAILED!\n";
            cout << "  Input: nums = [";
            for (size_t j = 0; j < input.size(); ++j) {
                if (j > 0) cout << ", ";
                cout << input[j];
            }
            cout << "], k = " << tests[i].k << "\n";
            cout << "  Expected: " << tests[i].expected << "\n";
            cout << "  Got:      " << result << "\n";
        }
    }

    if (all_passed) {
        cout << "✅ All test cases passed!" << endl;
    }

    return 0;
}
