#include <iostream>
#include <sstream>
#include <string>

#include "../../source/output/codestral/cpp/Task61_MISTRAL_codestral-latest.cpp"

// إذا الحل يحتوي parseXmlFromString فقط، أعْلِم extern هنا:
extern void parseXmlFromString();

bool test_parseXmlFromString() {
    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf()); // تحويل cout لالتقاط المخرجات

    parseXmlFromString();

    std::cout.rdbuf(oldCout); // استعادة cout

    std::string output = buffer.str();

    // نتحقق أن المخرجات تحتوي على اسم العنصر الجذر الصحيح
    return output.find("Root element: root") != std::string::npos;
}

int main() {
    int passed = 0;
    int failed = 0;

    if (test_parseXmlFromString()) {
        std::cout << "[PASS] test_parseXmlFromString" << std::endl;
        ++passed;
    } else {
        std::cout << "[FAIL] test_parseXmlFromString" << std::endl;
        ++failed;
    }

    std::cout << "------------------------" << std::endl;
    std::cout << "Passed " << passed << " out of 1 tests." << std::endl;

    return failed > 0 ? 1 : 0;
}
