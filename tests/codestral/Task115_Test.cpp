#include <iostream>
#include <cassert>

class BitFields {
private:
    unsigned int _data = 0;
public:
    // field1: lower 2 bits (bits 0-1)
    unsigned int getField1() const {
        return _data & 0b11;
    }
    void setField1(unsigned int value) {
        _data = (_data & ~0b11) | (value & 0b11);
    }

    // field2: bits 2-4 (3 bits)
    unsigned int getField2() const {
        return (_data >> 2) & 0b111;
    }
    void setField2(unsigned int value) {
        _data = (_data & ~(0b111 << 2)) | ((value & 0b111) << 2);
    }

    // field3: bit 5 (1 bit)
    unsigned int getField3() const {
        return (_data >> 5) & 0b1;
    }
    void setField3(unsigned int value) {
        _data = (_data & ~(0b1 << 5)) | ((value & 0b1) << 5);
    }
};

// ======= Test cases from the Python code logic =======
bool test_case_1() {
    BitFields bf;
    bf.setField1(3);
    if (bf.getField1() != 3) return false;
    return true;
}

bool test_case_2() {
    BitFields bf;
    bf.setField2(5);
    if (bf.getField2() != 5) return false;
    return true;
}

bool test_case_3() {
    BitFields bf;
    bf.setField3(1);
    if (bf.getField3() != 1) return false;
    return true;
}

bool test_case_4() {
    BitFields bf;
    bf.setField1(2);
    bf.setField2(6);
    bf.setField3(1);
    if (bf.getField1() != 2) return false;
    if (bf.getField2() != 6) return false;
    if (bf.getField3() != 1) return false;
    return true;
}

bool test_case_5() {
    BitFields bf;
    bf.setField1(4); // more than 2 bits, should be masked to 0
    if (bf.getField1() != (4 & 0b11)) return false;
    return true;
}

// Run all test cases and print results
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
