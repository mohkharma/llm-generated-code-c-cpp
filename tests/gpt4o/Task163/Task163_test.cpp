// Task_LongestRun_Test.cpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

// Provided function unchanged
int longestRun(const std::vector<int>& lst) {
    if (lst.empty()) {
        return 0;
    }
    int maxRun = 1;
    int currentRun = 1;
    for (size_t i = 1; i < lst.size(); ++i) {
        if (lst[i] == lst[i-1] + 1 || lst[i] == lst[i-1] - 1) {
            currentRun += 1;
        } else {
            maxRun = std::max(maxRun, currentRun);
            currentRun = 1;
        }
    }
    return std::max(maxRun, currentRun);
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
        {"5 4 2 1", 2},
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
