#include "../../source/output/gemini/cpp/Task55_GEMINI_gemini-1.5-pro-001.cpp"
#include <iostream>
#include <string>

int tests_run = 0;
int tests_passed = 0;

#define ASSERT_TRUE(condition) \
    do { \
        ++tests_run; \
        if (condition) { \
            std::cout << "[PASS] " << __func__ << "\n"; \
            ++tests_passed; \
        } else { \
            std::cout << "[FAIL] " << __func__ << "\n"; \
        } \
    } while(0)

#define ASSERT_FALSE(condition) ASSERT_TRUE(!(condition))

void test_valid_email() {
    ASSERT_TRUE(isValidEmail("test.email@example.com"));
}

void test_valid_email_with_digits() {
    ASSERT_TRUE(isValidEmail("user123@example.com"));
}

void test_valid_email_with_special_characters() {
    ASSERT_TRUE(isValidEmail("user+name@example.co.uk"));
}

void test_invalid_email_missing_at_symbol() {
    ASSERT_FALSE(isValidEmail("invalidemail.com"));
}

void test_invalid_email_double_at_symbol() {
    ASSERT_FALSE(isValidEmail("user@@example.com"));
}

void test_invalid_email_missing_domain() {
    ASSERT_FALSE(isValidEmail("user@.com"));
}

void test_invalid_email_multiple_dots_in_domain() {
    ASSERT_FALSE(isValidEmail("user@example..com"));
}

void test_invalid_email_missing_username() {
    ASSERT_FALSE(isValidEmail("@example.com"));
}

void test_invalid_email_special_characters_in_domain() {
    ASSERT_FALSE(isValidEmail("user@ex!ample.com"));
}

void test_invalid_email_short_tld() {
    ASSERT_FALSE(isValidEmail("user@example.c"));
}

int main() {
    test_valid_email();
    test_valid_email_with_digits();
    test_valid_email_with_special_characters();
    test_invalid_email_missing_at_symbol();
    test_invalid_email_double_at_symbol();
    test_invalid_email_missing_domain();
    test_invalid_email_multiple_dots_in_domain();
    test_invalid_email_missing_username();
    test_invalid_email_special_characters_in_domain();
    test_invalid_email_short_tld();

    std::cout << "\nTotal tests run: " << tests_run << "\n";
    std::cout << "Total tests passed: " << tests_passed << "\n";
    std::cout << "Total tests failed: " << (tests_run - tests_passed) << "\n";

    return 0;
}
