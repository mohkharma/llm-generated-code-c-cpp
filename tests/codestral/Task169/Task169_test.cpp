// Task169_Test.cpp
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <set>
#include <algorithm>

// الحل الجديد باستخدام multiset
std::vector<int> countSmaller(std::vector<int>& nums) {
    std::vector<int> result;
    std::multiset<int> sortedSet;
    for (int i = nums.size() - 1; i >= 0; i--) {
        auto it = sortedSet.upper_bound(nums[i]);
        int index = std::distance(sortedSet.begin(), it);
        result.push_back(index);
        sortedSet.insert(nums[i]);
    }
    std::reverse(result.begin(), result.end());
    return result;
}

bool runTest(const std::vector<int>& input, const std::vector<int>& expected) {
    std::vector<int> in = input;
    std::vector<int> result = countSmaller(in);
    if (result != expected) {
        std::cerr << "Test failed.\nInput: ";
        for (int x : input) std::cerr << x << " ";
        std::cerr << "\nExpected: ";
        for (int x : expected) std::cerr << x << " ";
        std::cerr << "\nGot: ";
        for (int x : result) std::cerr << x << " ";
        std::cerr << "\n";
        return false;
    }
    return true;
}

int main() {
    std::vector<std::pair<std::vector<int>, std::vector<int>>> testCases = {
        {{5, 2, 6, 1}, {2, 1, 1, 0}},
        {{-1}, {0}},
        {{-1, -1}, {0, 0}},
        {{1, 2, 3, 4}, {0, 0, 0, 0}},
        {{4, 3, 2, 1}, {3, 2, 1, 0}},
        {{2, 0, 1}, {2, 0, 0}},
        {{10, 3, 2, 5}, {3, 1, 0, 0}},
        {{1, 1, 1, 1}, {0, 0, 0, 0}},
        {{6, 1, 2, 7, 1}, {3, 0, 1, 1, 0}},
        {{5, 9, 2, 8, 6}, {1, 3, 0, 1, 0}}
    };

    bool allPassed = true;
    for (size_t i = 0; i < testCases.size(); ++i) {
        if (!runTest(testCases[i].first, testCases[i].second)) {
            std::cerr << "Test case " << (i + 1) << " failed.\n";
            allPassed = false;
        }
    }

    if (allPassed) {
        std::cout << "All test cases passed successfully.\n";
    }

    return 0;
}
