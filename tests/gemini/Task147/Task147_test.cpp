#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>

class Solution {
public:
    int findKthLargest(std::vector<int>& nums, int k) {
        std::sort(nums.begin(), nums.end());
        return nums[nums.size() - k];
    }
};

bool runTest(const std::string& inputNums, int k, int expected) {
    std::stringstream ss(inputNums);
    std::vector<int> nums;
    int num;
    while (ss >> num) {
        nums.push_back(num);
    }
    Solution sol;
    int result = sol.findKthLargest(nums, k);
    if (result == expected) {
        return true;
    } else {
        std::cerr << "Test failed.\nInput: " << inputNums << "\nk = " << k
                  << "\nExpected: " << expected << ", Got: " << result << "\n";
        return false;
    }
}

int main() {
    int failed = 0;

    failed += !runTest("3 2 1 5 6 4", 2, 5);
    failed += !runTest("7 10 4 3 20 15", 3, 10);
    failed += !runTest("1 1 1 1", 2, 1);
    failed += !runTest("-1 -3 -2 -4 -5", 1, -1);
    failed += !runTest("-10 -50 20 10 30 0", 4, 0);
    failed += !runTest("100", 1, 100);
    failed += !runTest("1 23 12 9 30 2 50", 7, 1);
    failed += !runTest("1 2 3 4 5", 1, 5);
    failed += !runTest("3 2 3 1 2 4 5 5 6", 4, 4);
    failed += !runTest("3 6 1 0 10 7 8 2 4 5 9", 10, 1);

    if (failed == 0) {
        std::cout << "All test cases passed!\n";
    } else {
        std::cout << failed << " test(s) failed.\n";
    }
    return failed;
}
