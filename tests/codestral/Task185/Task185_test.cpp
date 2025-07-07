// TaskXXX_Test.cpp

#include <iostream>
#include <vector>
#include <cmath>

#include "../../../source/output/codestral/cpp/Task185_MISTRAL_codestral-latest.cpp"

bool isClose(double a, double b, double tol = 1e-5) {
    return std::fabs(a - b) <= tol;
}

int main() {
    int passed = 0, total = 0;

    struct TestCase {
        std::vector<int> nums1;
        std::vector<int> nums2;
        double expected;
    };

    std::vector<TestCase> testCases = {
        {{1, 3}, {2}, 2.0},
        {{1, 2}, {3, 4}, 2.5},
        {{0, 0}, {0, 0}, 0.0},
        {{}, {1}, 1.0},
        {{2}, {}, 2.0},
        {{1, 2, 3}, {4, 5, 6, 7}, 4.0},
        {{1000000}, {1000001}, 1000000.5}
    };

    for (const auto& tc : testCases) {
        total++;
        double result = findMedianSortedArrays(const_cast<std::vector<int>&>(tc.nums1),
                                                const_cast<std::vector<int>&>(tc.nums2));
        if (isClose(result, tc.expected)) {
            std::cout << "Test Case " << total << " Passed.\n";
            passed++;
        } else {
            std::cout << "Test Case " << total << " Failed.\n";
            std::cout << "  Input: nums1 = [";
            for (size_t i = 0; i < tc.nums1.size(); ++i) {
                std::cout << tc.nums1[i] << (i + 1 < tc.nums1.size() ? ", " : "");
            }
            std::cout << "], nums2 = [";
            for (size_t i = 0; i < tc.nums2.size(); ++i) {
                std::cout << tc.nums2[i] << (i + 1 < tc.nums2.size() ? ", " : "");
            }
            std::cout << "]\n";
            std::cout << "  Expected: " << tc.expected << ", Got: " << result << "\n";
        }
    }

    std::cout << "\nTotal: " << passed << " / " << total << " test cases passed.\n";
    return 0;
}
