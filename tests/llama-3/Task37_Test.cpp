// Task55_Test.cpp

#include "../../source/output/llama-3/cpp/Task55_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"

#include <iostream>
#include <sstream>
#include <string>
#include <streambuf>

// التقاط المخرجات من getUserByUsername
std::string capture_output(const std::string& username) {
    std::ostringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    getUserByUsername(username);  // استدعاء الدالة

    std::cout.rdbuf(old);  // إعادة cout للوضع الطبيعي
    return buffer.str();
}

int main() {
    int passed = 0, failed = 0;

    std::cout << "Running test: test_existing_user" << std::endl;
    std::string output1 = capture_output("ahmad");
    if (output1.find("User found") != std::string::npos) {
        std::cout << "[PASS] test_existing_user" << std::endl;
        passed++;
    } else {
        std::cout << "[FAIL] test_existing_user\nOutput was:\n" << output1 << std::endl;
        failed++;
    }

    std::cout << "Running test: test_non_existing_user" << std::endl;
    std::string output2 = capture_output("nonexistent_user_xyz");
    if (output2.find("User not found") != std::string::npos) {
        std::cout << "[PASS] test_non_existing_user" << std::endl;
        passed++;
    } else {
        std::cout << "[FAIL] test_non_existing_user\nOutput was:\n" << output2 << std::endl;
        failed++;
    }

    std::cout << "===============================\n";
    std::cout << "Total Passed: " << passed << "\nTotal Failed: " << failed << std::endl;

    return failed == 0 ? 0 : 1;
}
