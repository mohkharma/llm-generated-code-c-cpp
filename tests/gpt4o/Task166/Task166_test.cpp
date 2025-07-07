#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

std::vector<int> posNegSort(const std::vector<int>& lst) {
    std::vector<int> pos_nums;
    for (int num : lst) {
        if (num > 0) pos_nums.push_back(num);
    }
    std::sort(pos_nums.begin(), pos_nums.end());

    std::vector<int> result;
    int pos_index = 0;
    for (int num : lst) {
        if (num > 0) {
            result.push_back(pos_nums[pos_index++]);
        } else {
            result.push_back(num);
        }
    }
    return result;
}

bool vectorsEqual(const std::vector<int>& a, const std::vector<int>& b) {
    return a.size() == b.size() && std::equal(a.begin(), a.end(), b.begin());
}

void run_tests() {
    assert(vectorsEqual(posNegSort({6, 3, -2, 5, -8, 2, -2}), {2, 3, -2, 5, -8, 6, -2}));
    assert(vectorsEqual(posNegSort({6, 5, 4, -1, 3, 2, -1, 1}), {1, 2, 3, -1, 4, 5, -1, 6}));
    assert(vectorsEqual(posNegSort({-5, -5, -5, -5, 7, -5}), {-5, -5, -5, -5, 7, -5}));
    assert(vectorsEqual(posNegSort({}), {}));
    assert(vectorsEqual(posNegSort({10, -10, 20, -20}), {10, -10, 20, -20}));
    assert(vectorsEqual(posNegSort({9, 3, -3, -2, 7}), {3, 7, -3, -2, 9}));
    assert(vectorsEqual(posNegSort({5, 4, -1, -2, 1}), {1, 4, -1, -2, 5}));
    assert(vectorsEqual(posNegSort({-3, -2, -1}), {-3, -2, -1}));
    assert(vectorsEqual(posNegSort({100, -50, 75, -25}), {75, -50, 100, -25}));
    assert(vectorsEqual(posNegSort({2, 1, -9, -8}), {1, 2, -9, -8}));

    std::cout << "ALL TESTS PASSED\n";
}

int main() {
    run_tests();
    return 0;
}
