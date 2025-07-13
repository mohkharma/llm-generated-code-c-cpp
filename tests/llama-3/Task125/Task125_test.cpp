#include <iostream>
#include <sstream>
#include <string>
#include "../../../source/output/llama-3/cpp/Task125_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"
int passed = 0, failed = 0;

void assertOutput(const std::string& input, const std::string& expected, const std::string& testName) {
    std::ostringstream outBuffer;
    std::streambuf* oldCout = std::cout.rdbuf(outBuffer.rdbuf());

    accessResource(input);  // call function with test input

    std::cout.rdbuf(oldCout);  // restore std::cout
    std::string output = outBuffer.str();

    if (output.find(expected) != std::string::npos) {
        std::cout << "[PASSED] " << testName << "\n";
        passed++;
    } else {
        std::cout << "[FAILED] " << testName << "\n";
        std::cout << "  Expected: \"" << expected << "\"\n";
        std::cout << "  Got: \"" << output << "\"\n";
        failed++;
    }
}

int main() {
    assertOutput("admin", "Access granted to admin resource", "test_admin");
    assertOutput("moderator", "Access granted to moderator resource", "test_moderator");
    assertOutput("user", "Access granted to user resource", "test_user");
    assertOutput("guest", "Access denied", "test_invalid_guest");
    assertOutput("", "Access denied", "test_empty");
    assertOutput("Admin", "Access denied", "test_case_sensitive");

    int total = passed + failed;
    double rate = total == 0 ? 0 : (passed * 100.0) / total;

    std::cout << "\n=== TEST SUMMARY ===\n";
    std::cout << "Total: " << total << "\n";
    std::cout << "Passed: " << passed << "\n";
    std::cout << "Failed: " << failed << "\n";
    std::cout << "Success Rate: " << rate << "%\n";

    if (failed == 0) {
        std::cout << "\n✅ All tests passed successfully.\n";
    }

    return failed == 0 ? 0 : 1;
}
