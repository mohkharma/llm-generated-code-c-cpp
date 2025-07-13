#include <iostream>
#include <sstream>
#include <string>
#include "../../../source/output/gpt4o/cpp/Task133_OPENAI_gpt-4o.cpp"

bool test_resetPassword_output(const std::string& username, const std::string& newPassword) {
    std::ostringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

    // استدعاء الدالة من الحل الخارجي
    resetPassword(username, newPassword);

    std::cout.rdbuf(oldCout); // استعادة cout الأصلي

    std::string expected = "Password for " + username + " has been reset to " + newPassword;

    std::string result = output.str();

    return result.find(expected) != std::string::npos;
}

int main() {
    int passed = 0, failed = 0;

    if (test_resetPassword_output("alice", "newPass123")) {
        std::cout << "[PASS] Test resetPassword for alice\n";
        passed++;
    } else {
        std::cout << "[FAIL] Test resetPassword for alice\n";
        failed++;
    }

    if (test_resetPassword_output("bob", "password456")) {
        std::cout << "[PASS] Test resetPassword for bob\n";
        passed++;
    } else {
        std::cout << "[FAIL] Test resetPassword for bob\n";
        failed++;
    }

    std::cout << "-----------------------\n";
    std::cout << "Passed: " << passed << "\nFailed: " << failed << "\n";

    return failed == 0 ? 0 : 1;
}
