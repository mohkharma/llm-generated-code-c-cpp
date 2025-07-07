// Task166_Test.cpp
#include <iostream>
#include <vector>
#include <sstream>
#include <cassert>
#include <algorithm>

// دالة posNegSort كما زودتني بها
std::vector<int> posNegSort(std::vector<int>& arr) {
    std::vector<int> pos;
    for (int num : arr) {
        if (num > 0) {
            pos.push_back(num);
        }
    }
    std::sort(pos.begin(), pos.end());
    int pos_i = 0;
    for (int i = 0; i < (int)arr.size(); i++) {
        if (arr[i] > 0) {
            arr[i] = pos[pos_i];
            pos_i += 1;
        }
    }
    return arr;
}

// دالة مساعدة لطباعة متجه الأعداد (اختياري للتتبع)
std::string vecToString(const std::vector<int>& v) {
    std::ostringstream oss;
    oss << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        oss << v[i];
        if (i + 1 != v.size()) oss << ", ";
    }
    oss << "]";
    return oss.str();
}

// اختبار منفرد
void check(const std::vector<int>& input, const std::vector<int>& expected, int test_num) {
    std::vector<int> copy = input; // نمرر نسخة غير ثابتة
    std::vector<int> result = posNegSort(copy);
    if (result != expected) {
        std::cerr << "Test case " << test_num << " FAILED.\n";
        std::cerr << "Input:    " << vecToString(input) << "\n";
        std::cerr << "Expected: " << vecToString(expected) << "\n";
        std::cerr << "Got:      " << vecToString(result) << "\n";
        assert(false); // يوقف البرنامج عند فشل أي اختبار
    }
}

// كل الاختبارات
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
