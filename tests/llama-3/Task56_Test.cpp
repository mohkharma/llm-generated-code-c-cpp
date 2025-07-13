#include "../../source/output/llama-3/cpp/Task56_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"
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

bool isHex(const std::string& str) {
    for (char c : str) {
        if (!std::isxdigit(static_cast<unsigned char>(c))) return false;
    }
    return true;
}

void test_token_is_64_characters_hex() {
    std::string token = generateToken("user", "pass");
    ASSERT_TRUE(token.length() == 64);
    ASSERT_TRUE(isHex(token));
}

void test_token_changes_on_second_call() {
    std::string t1 = generateToken("user", "pass");
    std::this_thread::sleep_for(std::chrono::seconds(1)); // حتى يختلف التوقيت
    std::string t2 = generateToken("user", "pass");
    ASSERT_TRUE(t1 != t2);
}

int main() {
    test_token_is_64_characters_hex();
    test_token_changes_on_second_call();

    std::cout << "\nTotal tests run: " << tests_run << "\n";
    std::cout << "Total tests passed: " << tests_passed << "\n";
    std::cout << "Total tests failed: " << (tests_run - tests_passed) << "\n";

    return 0;
}
