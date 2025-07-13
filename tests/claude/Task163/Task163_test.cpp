// Task_LongestRun_Test.cpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>

// Function under test (same as given solution)
int longestRun(const std::vector<int>& arr) {
    if (arr.empty()) return 0;
    int maxRun = 1, currentRun = 1;
    for (size_t i = 1; i < arr.size(); ++i) {
        if (std::abs(arr[i] - arr[i - 1]) == 1) {
            currentRun++;
            maxRun = std::max(maxRun, currentRun);
        } else {
            currentRun = 1;
        }
    }
    return maxRun;
}

// Helper to parse input string into vector<int>
std::vector<int> parseInput(const std::string& inputLine) {
    std::stringstream ss(inputLine);
    std::vector<int> result;
    int x;
    while (ss >> x) {
        result.push_back(x);
    }
    return result;
}

// Run one test case with simulated input/output like the Python test print statements
bool runTest(const std::string& input, int expected) {
    // Simulate reading an array of integers from input string
    std::vector<int> arr = parseInput(input);

    int result = longestRun(arr);

    if (result != expected) {
        std::cerr << "Test failed.\nInput array: [" << input << "]\nExpected: " << expected << "\nGot: " << result << "\n";
        return false;
    }
    return true;
}

int main() {
    // Define test cases exactly matching Python ones
    struct TestCase {
        std::string input;
        int expected;
    };

    TestCase tests[] = {
        {"1 2 3 5 6 7 8 9", 5},
        {"1 2 3 10 11 15", 3},
        {"5 4 2 1", 2},
        {"3 5 7 10 15", 1},
        {"", 0}  // Also test empty input
    };

    bool allPassed = true;
    for (const auto& test : tests) {
        if (!runTest(test.input, test.expected)) {
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
