#include <iostream>
#include <vector>
#include <cassert>

// Include the Solution class
class Solution {
public:
    bool xorGame(std::vector<int>& nums) {
        int xorSum = 0;
        for (int num : nums) {
            xorSum ^= num;
        }
        return xorSum == 0 || nums.size() % 2 == 0;
    }
};

// Test function to run test cases
void runTests() {
    Solution solution;
    bool passed = true;

    // Test Case 1: nums = [1, 1, 2], Expected: false
    std::vector<int> test1 = {1, 1, 2};
    bool result1 = solution.xorGame(test1);
    std::cout << "Test Case 1: nums = [1, 1, 2], Expected: false, Got: " << (result1 ? "true" : "false");
    if (result1 == false) {
        std::cout << " -> Passed" << std::endl;
    } else {
        std::cout << " -> Failed" << std::endl;
        passed = false;
    }

    // Test Case 2: nums = [0, 1], Expected: true
    std::vector<int> test2 = {0, 1};
    bool result2 = solution.xorGame(test2);
    std::cout << "Test Case 2: nums = [0, 1], Expected: true, Got: " << (result2 ? "true" : "false");
    if (result2 == true) {
        std::cout << " -> Passed" << std::endl;
    } else {
        std::cout << " -> Failed" << std::endl;
        passed = false;
    }

    // Test Case 3: nums = [1, 2, 3], Expected: true
    std::vector<int> test3 = {1, 2, 3};
    bool result3 = solution.xorGame(test3);
    std::cout << "Test Case 3: nums = [1, 2, 3], Expected: true, Got: " << (result3 ? "true" : "false");
    if (result3 == true) {
        std::cout << " -> Passed" << std::endl;
    } else {
        std::cout << " -> Failed" << std::endl;
        passed = false;
    }

    if (passed) {
        std::cout << "All tests passed!" << std::endl;
    } else {
        std::cout << "Some tests failed!" << std::endl;
    }
}

int main() {
    std::cout << "Running XOR Game Tests..." << std::endl;
    runTests();
    return 0;
}