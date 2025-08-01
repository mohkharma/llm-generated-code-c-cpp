#include "../../source/output/gpt4o/cpp/Task55_OPENAI_gpt-4o.cpp"

#include <iostream>
#include <sstream>
#include <string>
#include <streambuf>

// دالة لمساعدتنا على التقاط مخرجات cout
std::string capture_output(const std::string& username) {
    std::ostringstream output;
    std::streambuf* old = std::cout.rdbuf(output.rdbuf());

    getUserByUsername(username);  // استدعاء الدالة من الحل

    std::cout.rdbuf(old);  // إعادة cout للوضع الطبيعي
    return output.str();
}

int main() {
    int passed = 0, failed = 0;

    std::cout << "Running test: test_existing_user" << std::endl;
    std::string out1 = capture_output("ahmad");
    if (out1.find("User: ahmad") != std::string::npos) {
        std::cout << "[PASS] test_existing_user" << std::endl;
        passed++;
    } else {
        std::cout << "[FAIL] test_existing_user\nOutput was:\n" << out1 << std::endl;
        failed++;
    }

    std::cout << "Running test: test_non_existing_user" << std::endl;
    std::string out2 = capture_output("nonexistent_xyz");
    if (out2.empty()) {
        std::cout << "[PASS] test_non_existing_user" << std::endl;
        passed++;
    } else {
        std::cout << "[FAIL] test_non_existing_user\nOutput was:\n" << out2 << std::endl;
        failed++;
    }

    std::cout << "===============================\n";
    std::cout << "Total Passed: " << passed << "\nTotal Failed: " << failed << std::endl;

    return failed == 0 ? 0 : 1;
}
