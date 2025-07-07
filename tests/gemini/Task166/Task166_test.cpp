#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

// الدالة التي زودتني بها
std::vector<int> posNegSort(std::vector<int> arr) {
    if (arr.empty()) {
        return arr;
    }
    std::vector<int> posList;
    for (int i = 0; i < (int)arr.size(); i++) {
        if (arr[i] > 0) {
            posList.push_back(arr[i]);
        }
    }
    std::sort(posList.begin(), posList.end());
    int j = 0;
    for (int i = 0; i < (int)arr.size(); i++) {
        if (arr[i] > 0) {
            arr[i] = posList[j++];
        }
    }
    return arr;
}

// دالة مساعدة لطباعة المتجه (للتصحيح)
std::string toString(const std::vector<int>& v) {
    std::string s = "[";
    for (size_t i = 0; i < v.size(); ++i) {
        s += std::to_string(v[i]);
        if (i + 1 < v.size()) s += ", ";
    }
    s += "]";
    return s;
}

// دالة تحقق من اختبار واحد
void check(const std::vector<int>& input, const std::vector<int>& expected, int test_num) {
    auto output = posNegSort(input);
    if (output != expected) {
        std::cerr << "Test " << test_num << " FAILED\n";
        std::cerr << "Input:    " << toString(input) << "\n";
        std::cerr << "Expected: " << toString(expected) << "\n";
        std::cerr << "Got:      " << toString(output) << "\n";
        assert(false);
    }
}

// تشغيل كل الاختبارات
void run_tests() {
    check({6, 3, -2, 5, -8, 2, -2}, {2, 3, -2, 5, -8, 6, -2}, 1);
    check({6, 5, 4, -1, 3, 2, -1, 1}, {1, 2, 3, -1, 4, 5, -1, 6}, 2);
    check({-5, -5, -5, -5, 7, -5}, {-5, -5, -5, -5, 7, -5}, 3);
    check({}, {}, 4);
    check({10, -10, 20, -20}, {10, -10, 20, -20}, 5);
    check({9, 3, -3, -2, 7}, {3, 7, -3, -2, 9}, 6);
    check({5, 4, -1, -2, 1}, {1, 4, -1, -2, 5}, 7);
    check({-3, -2, -1}, {-3, -2, -1}, 8);
    check({100, -50, 75, -25}, {75, -50, 100, -25}, 9);
    check({2, 1, -9, -8}, {1, 2, -9, -8}, 10);

    std::cout << "ALL GOOD\n";
}

int main() {
    run_tests();
    return 0;
}
