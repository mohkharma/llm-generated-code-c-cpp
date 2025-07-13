#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include "../../../source/output/claude/cpp/Task124_CLAUDE_claude-3-5-sonnet-20240620.cpp"

int passed = 0, failed = 0;

void assertEqual(const std::string& actual, const std::string& expected, const std::string& testName) {
    if (actual == expected) {
        std::cout << "[PASSED] " << testName << "\n";
        passed++;
    } else {
        std::cout << "[FAILED] " << testName << "\n";
        std::cout << "  Expected: " << expected << "\n";
        std::cout << "  Actual:   " << actual << "\n";
        failed++;
    }
}

void assertThrows(const std::string& testName, const std::string& invalidInput) {
    try {
        decrypt(invalidInput);
        std::cout << "[FAILED] " << testName << "\n";
        std::cout << "  Expected exception, but none was thrown.\n";
        failed++;
    } catch (...) {
        std::cout << "[PASSED] " << testName << "\n";
        passed++;
    }
}

int main() {
    // Sensitive test data
    std::string credit_card = "1234-5678-9012-3456";
    std::string ssn = "123-45-6789";
    std::string password = "mySecretPass123";

    // 1. Encrypt/Decrypt credit card
    assertEqual(decrypt(encrypt(credit_card)), credit_card, "test_encrypt_credit_card");

    // 2. Encrypt/Decrypt SSN
    assertEqual(decrypt(encrypt(ssn)), ssn, "test_encrypt_ssn");

    // 3. Encrypt/Decrypt password
    assertEqual(decrypt(encrypt(password)), password, "test_encrypt_password");

    // 4. Encrypt/Decrypt empty string
    assertEqual(decrypt(encrypt("")), "", "test_encrypt_empty_string");

    // 5. Encrypt/Decrypt special characters
    std::string special = "!@#$%^&*()_+-=<>?";
    assertEqual(decrypt(encrypt(special)), special, "test_encrypt_special_characters");

    // 6. Decrypt empty string
    assertEqual(decrypt(encrypt("")), "", "test_decrypt_empty_string");

    // 7. Decrypt invalid base64 (simulate by passing a string not encrypted by our logic)
    assertThrows("test_decrypt_invalid_base64", "InvalidBase64");

    // 8. Encrypt/Decrypt long string
    std::string longStr(1000, 'A');
    assertEqual(decrypt(encrypt(longStr)), longStr, "test_encrypt_decrypt_with_long_string");

    // 9. Encrypt/Decrypt numeric string
    std::string numeric = "1234567890";
    assertEqual(decrypt(encrypt(numeric)), numeric, "test_encrypt_decrypt_with_numeric_string");

    // 10. Encrypt/Decrypt Unicode
    std::string unicode = "こんにちは";  // Japanese for "Hello"
    assertEqual(decrypt(encrypt(unicode)), unicode, "test_encrypt_decrypt_with_unicode");

    // Summary
    std::cout << "\n=== TEST SUMMARY ===\n";
    std::cout << "Passed: " << passed << "\n";
    std::cout << "Failed: " << failed << "\n";

    return failed == 0 ? 0 : 1;
}
