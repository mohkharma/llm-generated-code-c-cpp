#include <iostream>

struct PackedData {
    int value : 8;   // 8 bits
    int flag1 : 1;   // 1 bit
    int flag2 : 2;   // 2 bits
    int value2 : 5;  // 5 bits
};

// ====== Test cases مشابهة لكن لحجم الحقول ======

// ملاحظة: الحقول signed (int) فالقيم تتعامل كسالب/موجب حسب البت الأعلى,
// لكن نختبر ضمن القيم الموجبة لضمان توافق.

bool test_case_1() {
    PackedData pd{};
    pd.value = 127;  // max 8-bit signed int is 127
    return pd.value == 127;
}

bool test_case_2() {
    PackedData pd{};
    pd.flag1 = 1;
    return pd.flag1 == 1;
}

bool test_case_3() {
    PackedData pd{};
    pd.flag2 = 3;  // max 2-bit unsigned value = 3
    return pd.flag2 == 3;
}

bool test_case_4() {
    PackedData pd{};
    pd.value2 = 31; // max 5-bit unsigned = 31
    return pd.value2 == 31;
}

bool test_case_5() {
    PackedData pd{};
    pd.value = 300; // خارج نطاق 8-bit signed, سلوك implementation-defined
    // عادة يخزن البتات الأقل فقط (300 & 0xFF = 44)
    int expected = 300 & 0xFF;
    return pd.value == expected;
}

// تشغيل التستات واظهار النتائج

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
