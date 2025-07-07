#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

std::vector<int> posNegSort(std::vector<int> arr) {
    std::vector<int> pos;
    for (int x : arr) {
        if (x > 0) {
            pos.push_back(x);
        }
    }
    std::sort(pos.begin(), pos.end());
    int pos_index = 0;
    for (int i = 0; i < (int)arr.size(); i++) {
        if (arr[i] > 0) {
            arr[i] = pos[pos_index++];
        }
    }
    return arr;
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
