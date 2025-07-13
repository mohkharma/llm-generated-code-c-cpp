#include <iostream>
#include <string>
#include "../../../source/output/llama-3/cpp/Task124_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"

int passed = 0, failed = 0;

void assertEqual(const std::string& actual, const std::string& expected, const std::string& testName) {
    if (actual == expected) {
        std::cout << "[PASSED] " << testName << "\n";
        passed++;
    } else {
        std::cout << "[FAILED] " << testName << "\n";
        std::cout << "  Expected: \"" << expected << "\"\n";
        std::cout << "  Actual:   \"" << actual << "\"\n";
        failed++;
    }
}

int main() {
    // 1. Credit card
    SensitiveData cc("1234-5678-9012-3456");
    assertEqual(cc.getData(), "1234-5678-9012-3456", "test_credit_card");

    // 2. SSN
    SensitiveData ssn("123-45-6789");
    assertEqual(ssn.getData(), "123-45-6789", "test_ssn");

    // 3. Password
    SensitiveData pw("mySecretPass123");
    assertEqual(pw.getData(), "mySecretPass123", "test_password");

    // 4. Empty string
    SensitiveData empty("");
    assertEqual(empty.getData(), "", "test_empty_string");

    // 5. Special characters
    SensitiveData special("!@#$%^&*()_+-=<>?");
    assertEqual(special.getData(), "!@#$%^&*()_+-=<>?", "test_special_characters");

    // 6. Long string
    std::string longStr(1000, 'A');
    SensitiveData longData(longStr);
    assertEqual(longData.getData(), longStr, "test_long_string");

    // 7. Numeric string
    SensitiveData numeric("1234567890");
    assertEqual(numeric.getData(), "1234567890", "test_numeric_string");

    // 8. Unicode string
    SensitiveData unicode("こんにちは"); // Japanese
    assertEqual(unicode.getData(), "こんにちは", "test_unicode");

    // Summary
    std::cout << "\n=== TEST SUMMARY ===\n";
    std::cout << "Passed: " << passed << "\n";
    std::cout << "Failed: " << failed << "\n";

    return failed == 0 ? 0 : 1;
}
