#include <iostream>
#include <string>
#include <sstream>
#include "../../../source/output/gpt4o/cpp/Task124_OPENAI_gpt-4o.cpp"

int passed = 0, failed = 0;

void assertEqual(const std::string& actual, const std::string& expected, const std::string& testName) {
    if (actual == expected) {
        std::cout << "[PASSED] " << testName << "\n";
        passed++;
    } else {
        std::cout << "[FAILED] " << testName << "\n";
        std::cout << "  Expected: \"" << expected << "\", Got: \"" << actual << "\"\n";
        failed++;
    }
}

int main() {
    SensitiveData sd;

    // 1. Store and retrieve credit card
    sd.storeData("credit_card", "1234-5678-9012-3456");
    assertEqual(sd.retrieveData("credit_card"), "1234-5678-9012-3456", "test_store_credit_card");

    // 2. Store and retrieve SSN
    sd.storeData("ssn", "123-45-6789");
    assertEqual(sd.retrieveData("ssn"), "123-45-6789", "test_store_ssn");

    // 3. Store and retrieve password
    sd.storeData("password", "mySecretPass123");
    assertEqual(sd.retrieveData("password"), "mySecretPass123", "test_store_password");

    // 4. Store and retrieve empty string
    sd.storeData("empty", "");
    assertEqual(sd.retrieveData("empty"), "", "test_store_empty_string");

    // 5. Store and retrieve special characters
    sd.storeData("special", "!@#$%^&*()_+-=<>?");
    assertEqual(sd.retrieveData("special"), "!@#$%^&*()_+-=<>?", "test_store_special_characters");

    // 6. Retrieve empty key (not stored)
    assertEqual(sd.retrieveData("nonexistent"), "Data not found", "test_retrieve_nonexistent_key");

    // 7. Store and retrieve long string
    std::string longStr(1000, 'A');
    sd.storeData("long", longStr);
    assertEqual(sd.retrieveData("long"), longStr, "test_store_long_string");

    // 8. Store and retrieve numeric string
    sd.storeData("numeric", "1234567890");
    assertEqual(sd.retrieveData("numeric"), "1234567890", "test_store_numeric_string");

    // 9. Store and retrieve Unicode string
    std::string unicode = "こんにちは";  // Japanese
    sd.storeData("unicode", unicode);
    assertEqual(sd.retrieveData("unicode"), unicode, "test_store_unicode");

    // Summary
    std::cout << "\n=== TEST SUMMARY ===\n";
    std::cout << "Passed: " << passed << "\n";
    std::cout << "Failed: " << failed << "\n";

    return failed == 0 ? 0 : 1;
}
