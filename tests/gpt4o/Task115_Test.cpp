#include <iostream>

class BitFields {
public:
    unsigned int a : 1;
    unsigned int b : 2;
    unsigned int c : 3;

    BitFields() : a(0), b(0), c(0) {}
    BitFields(unsigned int a, unsigned int b, unsigned int c) : a(a), b(b), c(c) {}

    void display() const {
        std::cout << "a: " << a << ", b: " << b << ", c: " << c << std::endl;
    }
};

// ======= Test cases مشابهة لتناسب الحقول =======

bool test_case_1() {
    BitFields bf;
    bf.a = 1;  // max 1 bit = 1
    return bf.a == 1;
}

bool test_case_2() {
    BitFields bf;
    bf.b = 2;  // max 2 bits = 3, جربنا 2
    return bf.b == 2;
}

bool test_case_3() {
    BitFields bf;
    bf.c = 5;  // max 3 bits = 7, جربنا 5
    return bf.c == 5;
}

bool test_case_4() {
    BitFields bf;
    bf.a = 0;
    bf.b = 3;
    bf.c = 7;
    return (bf.a == 0) && (bf.b == 3) && (bf.c == 7);
}

bool test_case_5() {
    BitFields bf;
    bf.a = 2;  // 2 خارج نطاق 1 bit, يتخزن بت واحد أقل فقط => 0 (2&1=0)
    return bf.a == (2 & 1);
}

// ======= تشغيل التستات =======

int main() {
    int pass = 0, fail = 0;

    if (test_case_1()) { std::cout << "Test case 1: PASS\n"; pass++; } else { std::cout << "Test case 1: FAIL\n"; fail++; }
    if (test_case_2()) { std::cout << "Test case 2: PASS\n"; pass++; } else { std::cout << "Test case 2: FAIL\n"; fail++; }
    if (test_case_3()) { std::cout << "Test case 3: PASS\n"; pass++; } else { std::cout << "Test case 3: FAIL\n"; fail++; }
    if (test_case_4()) { std::cout << "Test case 4: PASS\n"; pass++; } else { std::cout << "Test case 4: FAIL\n"; fail++; }
    if (test_case_5()) { std::cout << "Test case 5: PASS\n"; pass++; } else { std::cout << "Test case 5: FAIL\n"; fail++; }

    std::cout << "Summary: " << pass << " passed, " << fail << " failed.\n";
    return 0;
}
