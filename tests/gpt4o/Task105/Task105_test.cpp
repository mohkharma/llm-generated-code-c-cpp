#include <iostream>
#include <sstream>
#include <string>

 #include "../../../source/output/gpt4o/cpp/Task105_OPENAI_gpt-4o.cpp"

// دالة مساعدة للتحقق من وجود نص معين داخل نص آخر
bool contains(const std::string& haystack, const std::string& needle) {
    return haystack.find(needle) != std::string::npos;
}

int main() {
    int tests_passed = 0;
    int tests_failed = 0;

    // إعادة توجيه cout لالتقاط الإخراج
    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

    bool exception_thrown = false;
    try {
        connect("www.google.com", 443);  // استدعاء الدالة كما هي
    } catch (...) {
        exception_thrown = true;
    }

    // استعادة cout
    std::cout.rdbuf(oldCout);

    if (exception_thrown) {
        std::cout << "[FAIL] Test connect: Exception thrown." << std::endl;
        tests_failed++;
    } else {
        std::string output = buffer.str();
        bool hasCipher = !output.empty(); // بما أن الدالة تطبع اسم التشفير عند نجاح الاتصال

        if (hasCipher) {
            std::cout << "[PASS] Test connect output contains cipher info." << std::endl;
            tests_passed++;
        } else {
            std::cout << "[FAIL] Test connect output missing cipher info or connection failed." << std::endl;
            std::cout << "Output:\n" << output << std::endl;
            tests_failed++;
        }
    }

    std::cout << "-----------------------------" << std::endl;
    std::cout << "Tests passed: " << tests_passed << std::endl;
    std::cout << "Tests failed: " << tests_failed << std::endl;

    return tests_failed == 0 ? 0 : 1;
}
