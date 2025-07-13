#include <iostream>
#include <fstream>
#include <string>

 #include "../../../source/output/llama-3/cpp/Task132_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"

// دالة مساعدة لقراءة آخر سطر في ملف اللوق
std::string readLastLine(const std::string& filename) {
    std::ifstream file(filename);
    std::string line, lastLine;
    while (std::getline(file, line)) {
        if (!line.empty()) lastLine = line;
    }
    return lastLine;
}

bool testLogEvent(const std::string& event) {
    std::string logFileName = "security_log.txt";

    // قراءة آخر سطر قبل تسجيل الحدث
    std::string prevLastLine = readLastLine(logFileName);

    // تسجيل الحدث باستخدام دالة الحل
    logEvent(event);

    // قراءة آخر سطر بعد التسجيل
    std::string newLastLine = readLastLine(logFileName);

    // تحقق أن السطر الجديد مختلف ويحتوي نص الحدث
    return (newLastLine != prevLastLine) && (newLastLine.find(event) != std::string::npos);
}

int main() {
    int passed = 0;
    int failed = 0;

    if (testLogEvent("User logged in")) {
        std::cout << "[PASS] Test 1: 'User logged in' event logged.\n";
        ++passed;
    } else {
        std::cout << "[FAIL] Test 1: 'User logged in' event NOT logged.\n";
        ++failed;
    }

    if (testLogEvent("File accessed: confidential.txt")) {
        std::cout << "[PASS] Test 2: 'File accessed: confidential.txt' event logged.\n";
        ++passed;
    } else {
        std::cout << "[FAIL] Test 2: 'File accessed: confidential.txt' event NOT logged.\n";
        ++failed;
    }

    std::cout << "------------------------\n";
    std::cout << "Passed: " << passed << "\nFailed: " << failed << "\n";

    return (failed == 0) ? 0 : 1;
}
