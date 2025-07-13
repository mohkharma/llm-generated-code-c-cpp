#include "../../source/output/codestral/cpp/Task56_MISTRAL_codestral-latest.cpp"
#include <iostream>
#include <string>
#include <cctype>
#include <thread>
#include <chrono>

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

bool isHexString(const std::string& s) {
    for (char c : s) {
        if (!std::isxdigit(static_cast<unsigned char>(c)))
            return false;
    }
    return true;
}

void test_token_length() {
    std::string token = generateToken("user", "pass");
    ASSERT_TRUE(token.length() == 64);
}

void test_token_is_hex() {
    std::string token = generateToken("user", "pass");
    ASSERT_TRUE(isHexString(token));
}

void test_tokens_are_unique() {
    std::string token1 = generateToken("user", "pass");
    // Sleep to ensure timestamp difference
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    std::string token2 = generateToken("user", "pass");
    ASSERT_TRUE(token1 != token2);
}

void test_different_credentials_produce_different_tokens() {
    std::string token1 = generateToken("user1", "pass1");
    std::string token2 = generateToken("user2", "pass2");
    ASSERT_TRUE(token1 != token2);
}

int main() {
    test_token_length();
    test_token_is_hex();
    test_tokens_are_unique();
    test_different_credentials_produce_different_tokens();

    std::cout << "\nTotal tests run: " << tests_run << "\n";
    std::cout << "Total tests passed: " << tests_passed << "\n";
    std::cout << "Total tests failed: " << (tests_run - tests_passed) << "\n";

    return 0;
}
