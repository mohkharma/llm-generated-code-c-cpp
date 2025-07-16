#include "../../source/output/claude/cpp/Task37_CLAUDE_claude-3-5-sonnet-20240620.cpp"  // Include the header for the function

#include <iostream>
#include <sstream>
#include <string>
#include <streambuf>

std::string capture_output(const std::string& username) {
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    get_user_info(username);  // استدعاء الدالة من الحل

    std::cout.rdbuf(old);  // استرجاع cout للوضع الطبيعي
    return buffer.str();
}

int main() {
    int passed = 0;
    int failed = 0;

    std::cout << "Running test: test_existing_user" << std::endl;
    std::string output1 = capture_output("ahmad");
    if (output1.find("User found") != std::string::npos) {
        std::cout << "[PASS] test_existing_user" << std::endl;
        passed++;
    } else {
        std::cout << "[FAIL] test_existing_user" << std::endl;
        std::cout << "Output was:\n" << output1 << std::endl;
        failed++;
    }

    std::cout << "Running test: test_non_existing_user" << std::endl;
    std::string output2 = capture_output("nonexistent_user_xyz");
    if (output2.find("User not found") != std::string::npos) {
        std::cout << "[PASS] test_non_existing_user" << std::endl;
        passed++;
    } else {
        std::cout << "[FAIL] test_non_existing_user" << std::endl;
        std::cout << "Output was:\n" << output2 << std::endl;
        failed++;
    }

    std::cout << "===============================" << std::endl;
    std::cout << "Total Passed: " << passed << std::endl;
    std::cout << "Total Failed: " << failed << std::endl;

    return failed == 0 ? 0 : 1;
}
