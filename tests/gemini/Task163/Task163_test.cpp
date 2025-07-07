// Task_LongestRun_Test.cpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

// The given longestRun function exactly as provided
int longestRun(std::vector<int> arr) {
    if (arr.size() <= 1) {
        return arr.size();
    }

    int maxRun = 1;
    int currentRun = 1;

    for (size_t i = 1; i < arr.size(); i++) {
        if (arr[i] == arr[i - 1] + 1 || arr[i] == arr[i - 1] - 1) {
            currentRun++;
        } else {
            currentRun = 1;
        }

        maxRun = std::max(maxRun, currentRun);
    }

    return maxRun;
}

// Helper to parse a line of integers into vector<int>
std::vector<int> parseInput(const std::string& line) {
    std::stringstream ss(line);
    std::vector<int> result;
    int x;
    while (ss >> x) {
        result.push_back(x);
    }
    return result;
}

// Runs a single test case, returns true if passed, false otherwise
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
        {"", 0}  // Test empty array returns 0
    };

    bool allPassed = true;
    for (const auto& t : tests) {
        if (!runTest(t.input, t.expected)) {
            allPassed = false;
        }
    }

    if (allPassed) {
        std::cout << "All tests passed successfully.\n";
        return 0;
    } else {
        std::cerr << "Some tests failed.\n";
        return 1;
    }
}
