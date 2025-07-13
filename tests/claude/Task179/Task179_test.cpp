#include <iostream>
#include <vector>
#include <sstream>
#include <string>

#include "../../../source/output/claude/cpp/Task179_CLAUDE_claude-3-5-sonnet-20240620.cpp"

bool isEqual(const std::vector<int>& a, const std::vector<int>& b) {
    if (a.size() != b.size()) return false;
    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

void printVector(const std::vector<int>& vec) {
    std::cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i != vec.size() - 1) std::cout << ", ";
    }
    std::cout << "]";
}

int main() {
    Solution solution;
    int passed = 0, total = 10;

    struct TestCase {
        std::vector<int> input;
        int k;
        std::vector<int> expected;
    };

    std::vector<TestCase> tests = {
        {{1,3,-1,-3,5,3,6,7}, 3, {3,3,5,5,6,7}},
        {{1}, 1, {1}},
        {{1,-1}, 1, {1, -1}},
        {{9,11}, 2, {11}},
        {{4,-2}, 2, {4}},
        {{7,2,4}, 2, {7,4}},
        {{1,3,1,2,0,5}, 3, {3,3,2,5}},
        {{1,2,3,4,5,6,7,8,9}, 3, {3,4,5,6,7,8,9}},
        {{10,9,8,7,6,5,4,3,2,1}, 4, {10,9,8,7,6,5,4}},
        {{5,5,5,5,5}, 2, {5,5,5,5}}
    };

    for (size_t i = 0; i < tests.size(); ++i) {
        std::vector<int> result = solution.maxSlidingWindow(tests[i].input, tests[i].k);
        if (isEqual(result, tests[i].expected)) {
            passed++;
        } else {
            std::cout << "Test Case " << i + 1 << " Failed!\n";
            std::cout << "  Input: nums = ";
            printVector(tests[i].input);
            std::cout << ", k = " << tests[i].k << "\n";
            std::cout << "  Expected: ";
            printVector(tests[i].expected);
            std::cout << "\n";
            std::cout << "  Got:      ";
            printVector(result);
            std::cout << "\n";
        }
    }

    if (passed == total) {
        std::cout << "All test cases passed!\n";
    } else {
        std::cout << passed << " out of " << total << " test cases passed.\n";
    }

    return 0;
}
