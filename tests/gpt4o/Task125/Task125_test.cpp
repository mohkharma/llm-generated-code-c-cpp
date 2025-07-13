#include <iostream>
#include <string>
#include <vector>
#include "../../../source/output/gpt4o/cpp/Task125_OPENAI_gpt-4o.cpp"

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
    assertEqual(accessResource("admin"), "Access to administrative resources granted.", "test_admin");
    assertEqual(accessResource("user"), "Access to user resources granted.", "test_user");
    assertEqual(accessResource("guest"), "Access to guest resources granted.", "test_guest");
    assertEqual(accessResource("visitor"), "No resources available for this user role", "test_invalid_role");
    assertEqual(accessResource(""), "No resources available for this user role", "test_empty_role");
    assertEqual(accessResource("Admin"), "No resources available for this user role", "test_case_sensitive");
    assertEqual(accessResource("ADMIN"), "No resources available for this user role", "test_uppercase_role");

    int total = passed + failed;
    double successRate = total == 0 ? 0 : (passed * 100.0) / total;

    std::cout << "\n=== TEST SUMMARY ===\n";
    std::cout << "Total: " << total << "\n";
    std::cout << "Passed: " << passed << "\n";
    std::cout << "Failed: " << failed << "\n";
    std::cout << "Success Rate: " << successRate << "%\n";

    if (failed == 0) {
        std::cout << "\n✅ All tests passed successfully.\n";
    }

    return failed == 0 ? 0 : 1;
}
