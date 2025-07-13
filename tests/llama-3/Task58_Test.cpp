#include "../../source/output/llama-3/cpp/Task58_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"

#include <iostream>
#include <string>

int tests_run = 0;
int tests_passed = 0;

#define ASSERT_TRUE(condition) \
do { \
++tests_run; \
if ((condition)) { \
std::cout << "[PASS] " << __func__ << "\n"; \
++tests_passed; \
} else { \
std::cout << "[FAIL] " << __func__ << "\n"; \
} \
} while (0)

#define ASSERT_FALSE(condition) ASSERT_TRUE(!(condition))

void test_all_x_and_o() {
    ASSERT_TRUE(xo("ooxx"));
}

void test_more_x_than_o() {
    ASSERT_FALSE(xo("xooxx"));
}

void test_more_o_than_x() {
    ASSERT_TRUE(xo("xxoo"));
}

void test_case_insensitive() {
    ASSERT_TRUE(xo("ooxXm"));
}

void test_no_x_no_o() {
    ASSERT_TRUE(xo("zpzpzpp"));
}

void test_no_x_with_o() {
    ASSERT_FALSE(xo("zzoo"));
}

void test_no_o_with_x() {
    ASSERT_FALSE(xo("xxxx"));
}

void test_empty_string() {
    ASSERT_TRUE(xo(""));
}

void test_single_character_o() {
    ASSERT_FALSE(xo("o"));
}

void test_single_character_x() {
    ASSERT_FALSE(xo("x"));
}

int main() {
    test_all_x_and_o();
    test_more_x_than_o();
    test_more_o_than_x();
    test_case_insensitive();
    test_no_x_no_o();
    test_no_x_with_o();
    test_no_o_with_x();
    test_empty_string();
    test_single_character_o();
    test_single_character_x();

    std::cout << "\nTotal: " << tests_run << " tests run.\n";
    std::cout << "Passed: " << tests_passed << "\n";
    std::cout << "Failed: " << (tests_run - tests_passed) << "\n";

    return 0;
}
