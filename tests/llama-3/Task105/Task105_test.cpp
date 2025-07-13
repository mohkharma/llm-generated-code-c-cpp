#include <iostream>
#include <sstream>
#include <string>

// تضمين ملف الحل — غيّر المسار حسب موقعك الحقيقي
#include "../../../source/output/llama-3/cpp/Task105_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"

// دالة مساعدة لفحص وجود نص في الإخراج
bool contains(const std::string& haystack, const std::string& needle) {
    return haystack.find(needle) != std::string::npos;
}

int main() {
    int tests_passed = 0;
    int tests_failed = 0;

    // إعادة توجيه cout لالتقاط المخرجات
    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

    bool exception_thrown = false;
    try {
        performSSLCommunication();
    } catch (...) {
        exception_thrown = true;
    }

    // استعادة cout
    std::cout.rdbuf(oldCout);

    if (exception_thrown) {
        std::cout << "[FAIL] Test performSSLCommunication: Exception thrown." << std::endl;
        tests_failed++;
    } else {
        std::string output = buffer.str();

        if (contains(output, "SSL connection established")) {
            std::cout << "[PASS] Test performSSLCommunication: Connection established message found." << std::endl;
            tests_passed++;
        } else {
            std::cout << "[FAIL] Test performSSLCommunication: Expected output missing." << std::endl;
            std::cout << "Output:\n" << output << std::endl;
            tests_failed++;
        }
    }

    std::cout << "-----------------------------" << std::endl;
    std::cout << "Tests passed: " << tests_passed << std::endl;
    std::cout << "Tests failed: " << tests_failed << std::endl;

    return tests_failed == 0 ? 0 : 1;
}
