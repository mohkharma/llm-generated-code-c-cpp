#include <iostream>
#include <cassert>
#include <cstdint>

struct BitFields {
    uint8_t field1 : 2;
    uint8_t field2 : 3;
    uint8_t field3 : 1;
    uint8_t : 2;  // padding
};

// =========== Test cases =============

// لأن bit-fields تخزن القيم مباشرة، ما نحتاج mask يدوياً، فقط تعيين وقراءة

bool test_case_1() {
    BitFields bf{};
    bf.field1 = 3;   // 0b11 max for 2 bits
    return bf.field1 == 3;
}

bool test_case_2() {
    BitFields bf{};
    bf.field2 = 5;  // 0b101 max for 3 bits
    return bf.field2 == 5;
}

bool test_case_3() {
    BitFields bf{};
    bf.field3 = 1;  // 1 bit
    return bf.field3 == 1;
}

bool test_case_4() {
    BitFields bf{};
    bf.field1 = 2;
    bf.field2 = 6;  // 6 fits in 3 bits (0b110)
    bf.field3 = 1;
    return (bf.field1 == 2) && (bf.field2 == 6) && (bf.field3 == 1);
}

bool test_case_5() {
    BitFields bf{};
    bf.field1 = 4;  // 4 = 0b100 but field1 is 2 bits, so only lower 2 bits stored
                    // this is implementation-defined but normally bits truncated
    // Expected: stored value = 0 (4 & 0b11 = 0)
    return bf.field1 == (4 & 0b11);
}

// ============ Run tests and print results ==============

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
