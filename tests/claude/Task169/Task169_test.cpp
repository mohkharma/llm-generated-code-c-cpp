// Task169_Test.cpp
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <cassert>

class Solution {
private:
    std::vector<int> count;
    std::vector<int> indexes;
    std::vector<int> temp;

    void mergeSort(std::vector<int>& nums, int start, int end) {
        if (start >= end) return;

        int mid = start + (end - start) / 2;
        mergeSort(nums, start, mid);
        mergeSort(nums, mid + 1, end);

        merge(nums, start, mid, end);
    }

    void merge(std::vector<int>& nums, int start, int mid, int end) {
        for (int i = start; i <= end; i++) {
            temp[i] = indexes[i];
        }

        int i = start, j = mid + 1, k = start;
        while (i <= mid && j <= end) {
            if (nums[temp[i]] <= nums[temp[j]]) {
                indexes[k] = temp[i];
                count[temp[i]] += j - (mid + 1);
                i++;
            } else {
                indexes[k] = temp[j];
                j++;
            }
            k++;
        }
        while (i <= mid) {
            indexes[k] = temp[i];
            count[temp[i]] += end - mid;
            i++; k++;
        }
        while (j <= end) {
            indexes[k++] = temp[j++];
        }
    }

public:
    std::vector<int> countSmaller(std::vector<int>& nums) {
        int n = nums.size();
        count.assign(n, 0);
        indexes.resize(n);
        temp.resize(n);
        for (int i = 0; i < n; ++i) indexes[i] = i;
        mergeSort(nums, 0, n - 1);
        return count;
    }
};

bool runTest(const std::vector<int>& input, const std::vector<int>& expected) {
    Solution solution;
    std::vector<int> in = input; // to preserve original input
    std::vector<int> result = solution.countSmaller(in);
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
