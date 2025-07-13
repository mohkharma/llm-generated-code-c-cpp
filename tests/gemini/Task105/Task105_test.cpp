#include <iostream>
#include <sstream>
#include <string>

 #include "../../../source/output/gemini/cpp/Task105_GEMINI_gemini-1.5-pro-001.cpp"

// دالة مساعدة لفحص وجود نص في الإخراج
bool contains(const std::string& haystack, const std::string& needle) {
    return haystack.find(needle) != std::string::npos;
}
int main() {
    int tests_passed = 0;
    int tests_failed = 0;

    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

    bool exception_thrown = false;

    try {
        establishSSLConnection();
    } catch (...) {
        exception_thrown = true;
    }

    std::cout.rdbuf(oldCout);

    if (exception_thrown) {
        std::cout << "[FAIL] Test establishSSLConnection: Exception thrown." << std::endl;
        tests_failed++;
    } else {
        std::string output = buffer.str();
        bool hasVersion = contains(output, "SSL/TLS version:");
        bool hasCipher = contains(output, "Cipher suite:");

        if (hasVersion && hasCipher) {
            std::cout << "[PASS] Test establishSSLConnection output contains expected info." << std::endl;
            tests_passed++;
        } else {
            std::cout << "[FAIL] Test establishSSLConnection output missing expected lines." << std::endl;
            std::cout << "Output:\n" << output << std::endl;
            tests_failed++;
        }
    }

    std::cout << "-----------------------------" << std::endl;
    std::cout << "Tests passed: " << tests_passed << std::endl;
    std::cout << "Tests failed: " << tests_failed << std::endl;

    return tests_failed == 0 ? 0 : 1;
}
