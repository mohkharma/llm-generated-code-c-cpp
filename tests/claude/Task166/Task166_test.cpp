// Task166_Test.cpp
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <cassert>
#include <algorithm>

// Solution class as given
class Solution {
public:
    std::vector<int> posNegSort(std::vector<int>& arr) {
        std::vector<int> pos;
        for (int num : arr) {
            if (num > 0) {
                pos.push_back(num);
            }
        }
        std::sort(pos.begin(), pos.end());

        std::vector<int> result;
        int posIndex = 0;
        for (int num : arr) {
            if (num > 0) {
                result.push_back(pos[posIndex++]);
            } else {
                result.push_back(num);
            }
        }
        return result;
    }
};

// Test class replicating the Python test logic exactly
class TestPosNegSort {
public:
    void run_all_tests() {
        test_case_1();
        test_case_2();
        test_case_3();
        test_case_4();
        test_case_5();
        test_case_6();
        test_case_7();
        test_case_8();
        test_case_9();
        test_case_10();
        std::cout << "ALL GOOD\n";
    }

private:
    void test_case_1() {
        check({6, 3, -2, 5, -8, 2, -2}, {2, 3, -2, 5, -8, 6, -2});
    }
    void test_case_2() {
        check({6, 5, 4, -1, 3, 2, -1, 1}, {1, 2, 3, -1, 4, 5, -1, 6});
    }
    void test_case_3() {
        check({-5, -5, -5, -5, 7, -5}, {-5, -5, -5, -5, 7, -5});
    }
    void test_case_4() {
        check({}, {});
    }
    void test_case_5() {
        check({10, -10, 20, -20}, {10, -10, 20, -20});
    }
    void test_case_6() {
        check({9, 3, -3, -2, 7}, {3, 7, -3, -2, 9});
    }
    void test_case_7() {
        check({5, 4, -1, -2, 1}, {1, 4, -1, -2, 5});
    }
    void test_case_8() {
        check({-3, -2, -1}, {-3, -2, -1});
    }
    void test_case_9() {
        check({100, -50, 75, -25}, {75, -50, 100, -25});
    }
    void test_case_10() {
        check({2, 1, -9, -8}, {1, 2, -9, -8});
    }

    void check(const std::vector<int>& input, const std::vector<int>& expected) {
        Solution sol;
        std::vector<int> arr = input;  // Copy to non-const for passing to function
        std::vector<int> output = sol.posNegSort(arr);
        assert(output == expected);
    }
};

int main() {
    TestPosNegSort tester;
    tester.run_all_tests();
    return 0;
}
