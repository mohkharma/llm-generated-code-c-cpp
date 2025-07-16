#include <iostream>

struct BitFields {
    unsigned int a : 1;
    unsigned int b : 2;
    unsigned int c : 3;
};

// ======= Test cases =======

bool test_case_1() {
    BitFields bf{};
    bf.a = 1;  // max 1 bit = 1
    return bf.a == 1;
}

bool test_case_2() {
    BitFields bf{};
    bf.b = 2;  // max 2 bits = 3
    return bf.b == 2;
}

bool test_case_3() {
    BitFields bf{};
    bf.c = 3;  // max 3 bits = 7
    return bf.c == 3;
}

bool test_case_4() {
    BitFields bf{};
    bf.a = 0;
    bf.b = 3;
    bf.c = 7;
    return (bf.a == 0) && (bf.b == 3) && (bf.c == 7);
}

bool test_case_5() {
    BitFields bf{};
    bf.a = 2;  // 2 خارج نطاق 1 bit => يخزن أقل بت (2 & 1 = 0)
    return bf.a == (2 & 1);
}

// ======= Main run tests =======

int main() {
    int pass_count = 0;
    int fail_count = 0;

    if (test_case_1()) { std::cout << "Test case 1: PASS\n"; pass_count++; } else { std::cout << "Test case 1: FAIL\n"; fail_count++; }
    if (test_case_2()) { std::cout << "Test case 2: PASS\n"; pass_count++; } else { std::cout << "Test case 2: FAIL\n"; fail_count++; }
    if (test_case_3()) { std::cout << "Test case 3: PASS\n"; pass_count++; } else { std::cout << "Test case 3: FAIL\n"; fail_count++; }
    if (test_case_4()) { std::cout << "Test case 4: PASS\n"; pass_count++; } else { std::cout << "Test case 4: FAIL\n"; fail_count++; }
    if (test_case_5()) { std::cout << "Test case 5: PASS\n"; pass_count++; } else { std::cout << "Test case 5: FAIL\n"; fail_count++; }

    std::cout << "Summary: " << pass_count << " passed, " << fail_count << " failed.\n";

    return 0;
}
