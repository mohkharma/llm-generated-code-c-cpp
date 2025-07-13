#include <iostream>
#include <sstream>
#include <string>
#include "../../../source/output/claude/cpp/Task133_CLAUDE_claude-3-5-sonnet-20240620.cpp"

bool test_resetPassword_output(const std::string& username) {
    std::stringstream buffer;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(buffer.rdbuf());

    // استدعاء الدالة من الحل الخارجي (resetPassword)
    std::string newPassword = resetPassword(username);

    std::cout.rdbuf(oldCoutBuffer); // استعادة cout الأصلي

    std::string output = buffer.str();

    // تحقق أن الرسائل الأساسية موجودة
    bool hasResetMsg = output.find("Password for " + username + " has been reset.") != std::string::npos;
    bool hasNewPassMsg = output.find("New password: ") != std::string::npos;
    bool newPassNonEmpty = !newPassword.empty();

    return hasResetMsg && hasNewPassMsg && newPassNonEmpty;
}

int main() {
    int passed = 0, failed = 0;

    // اختبار 1: اسم مستخدم عادي
    if (test_resetPassword_output("alice")) {
        std::cout << "[PASS] Test reset password for user 'alice'\n";
        passed++;
    } else {
        std::cout << "[FAIL] Test reset password for user 'alice'\n";
        failed++;
    }

    // اختبار 2: اسم مستخدم مختلف
    if (test_resetPassword_output("bob123")) {
        std::cout << "[PASS] Test reset password for user 'bob123'\n";
        passed++;
    } else {
        std::cout << "[FAIL] Test reset password for user 'bob123'\n";
        failed++;
    }

    // اختبار 3: اسم مستخدم فارغ (اختبار حافة)
    if (test_resetPassword_output("")) {
        std::cout << "[PASS] Test reset password for empty username\n";
        passed++;
    } else {
        std::cout << "[FAIL] Test reset password for empty username\n";
        failed++;
    }

    std::cout << "-------------------------\n";
    std::cout << "Passed: " << passed << "\nFailed: " << failed << "\n";

    return failed == 0 ? 0 : 1;
}
