#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// دالتك الأصلية بدون تعديل
std::string tweakLetters(std::string word, int tweaks[]) {
    std::string result = "";
    for (int i = 0; i < (int)word.length(); i++) {
        result += word[i] + tweaks[i];
    }
    return result;
}

// دالة مساعدة لتحويل vector إلى array
int* vecToArr(const std::vector<int>& v) {
    int* arr = new int[v.size()];
    for (size_t i = 0; i < v.size(); i++) {
        arr[i] = v[i];
    }
    return arr;
}

void run_tests() {
    struct TestCase {
        std::string input_word;
        std::vector<int> tweaks_vec;
        std::string expected;
    };

    TestCase tests[] = {
        {"apple", {0, 1, -1, 0, -1}, "aqold"},
        {"many", {0, 0, 0, -1}, "manx"},
        {"rhino", {1, 1, 1, 1, 1}, "sijop"},
        {"abc", {1, 1, 1}, "bcd"},
        {"xyz", {1, 1, 1}, "yza"},
        {"hello", {-1, 0, 1, 0, -1}, "gemln"},
        {"test", {-1, -1, -1, -1}, "sdrs"},
        {"abcd", {1, 2, 3, 4}, "bdfh"},
        {"zzz", {-1, -1, -1}, "yyy"},
        {"world", {0, 1, -1, 2, -2}, "wpqnb"}
    };

    bool all_passed = true;
    for (int i = 0; i < 10; ++i) {
        int* tweaks_arr = vecToArr(tests[i].tweaks_vec);
        std::string output = tweakLetters(tests[i].input_word, tweaks_arr);
        delete[] tweaks_arr;

        if (output != tests[i].expected) {
            std::cerr << "Test case " << (i+1) << " FAILED.\n";
            std::cerr << "Input word: " << tests[i].input_word << "\n";
            std::cerr << "Expected: " << tests[i].expected << "\n";
            std::cerr << "Got:      " << output << "\n\n";
            all_passed = false;
        }
    }

    if (all_passed) {
        std::cout << "all Task Good\n";
    }
}

int main() {
    run_tests();
    return 0;
}
