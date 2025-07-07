// Task_LongestRun_Test.cpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

// Provided function (with sorting)
int longestRun(std::vector<int> nums) {
    if (nums.empty()) {
        return 0;
    }
    std::sort(nums.begin(), nums.end());
    int longest_run = 1;
    int current_run = 1;
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] - nums[i-1] == 1) {
            current_run += 1;
        } else {
            longest_run = std::max(longest_run, current_run);
            current_run = 1;
        }
    }
    return std::max(longest_run, current_run);
}

// Parse input string to vector<int>
std::vector<int> parseInput(const std::string& line) {
    std::stringstream ss(line);
    std::vector<int> vec;
    int val;
    while (ss >> val) {
        vec.push_back(val);
    }
    return vec;
}

bool runTest(const std::string& input, int expected) {
    std::vector<int> arr = parseInput(input);
    int result = longestRun(arr);
    if (result != expected) {
        std::cerr << "Test failed.\nInput: [" << input << "]\nExpected: " << expected << ", Got: " << result << "\n";
        return false;
    }
    return true;
}

int main() {
    struct TestCase {
        std::string input;
        int expected;
    };

    TestCase tests[] = {
        {"1 2 3 5 6 7 8 9", 5},
        {"1 2 3 10 11 15", 3},
        {"5 4 2 1", 2},  // Note: sorting means [1,2,4,5] so longest consecutive run might differ
        {"3 5 7 10 15", 1},
        {"", 0}
    };

    bool all_passed = true;
    for (const auto& test : tests) {
        if (!runTest(test.input, test.expected)) {
            all_passed = false;
        }
    }

    if (all_passed) {
        std::cout << "All tests passed successfully.\n";
        return 0;
    } else {
        std::cerr << "Some tests failed.\n";
        return 1;
    }
}
