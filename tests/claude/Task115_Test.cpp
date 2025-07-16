#include <stdio.h>
#include <stdint.h>

struct BitFields {
    uint8_t field1 : 2;
    uint8_t field2 : 3;
    uint8_t field3 : 1;
    uint8_t : 2;  // padding
};

// دالة مساعدة للطباعة والنتيجة
void test_case(const char* test_name, int condition) {
    if (condition) {
        printf("%s: PASS\n", test_name);
    } else {
        printf("%s: FAIL\n", test_name);
    }
}

int main() {
    struct BitFields bf = {0};

    // Test 1: Set and get field1 (2 bits) with max value 3
    bf.field1 = 3;
    test_case("Test field1 max value", bf.field1 == 3);

    // Test 2: Set and get field1 with value overflow (e.g., 5 -> should store 1 because 2 bits)
    bf.field1 = 5;
    test_case("Test field1 overflow value", bf.field1 == (5 & 0b11));

    // Test 3: Set and get field2 (3 bits) with max value 7
    bf.field2 = 7;
    test_case("Test field2 max value", bf.field2 == 7);

    // Test 4: Set and get field2 with overflow value (e.g., 10 -> 2 because 10 & 0b111 = 2)
    bf.field2 = 10;
    test_case("Test field2 overflow value", bf.field2 == (10 & 0b111));

    // Test 5: Set and get field3 (1 bit) with max value 1
    bf.field3 = 1;
    test_case("Test field3 max value", bf.field3 == 1);

    // Test 6: Set and get field3 with overflow value (e.g., 3 -> 1 because 3 & 0b1 = 1)
    bf.field3 = 3;
    test_case("Test field3 overflow value", bf.field3 == (3 & 0b1));

    // Test 7: Set all fields and verify independently
    bf.field1 = 2;
    bf.field2 = 5;
    bf.field3 = 0;
    test_case("Test all fields set/get", (bf.field1 == 2) && (bf.field2 == 5) && (bf.field3 == 0));

    return 0;
}
