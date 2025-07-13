#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

 #include "../../../source/output/claude/cpp/Task132_CLAUDE_claude-3-5-sonnet-20240620.cpp"

// دالة مساعدة لقراءة آخر سطر من ملف اللوق للتحأكد من تسجيل الحدث
std::string readLastLogLine(const std::string& filename) {
    std::ifstream file(filename);
    std::string line, lastLine;
    while (std::getline(file, line)) {
        if (!line.empty())
            lastLine = line;
    }
    return lastLine;
}

// دالة اختبار حالة واحدة
bool testLogEvent(const std::string& eventType, const std::string& description) {
    // قبل تسجيل الحدث، نقرأ آخر سطر في ملف اللوق (أو لا شيء إذا الملف جديد)
    std::string prevLastLine = readLastLogLine("security_events.log");

    // استدعاء دالة الحل (لن يتم تعديلها أبداً)
    logEvent(eventType, description);

    // قراءة آخر سطر بعد تسجيل الحدث
    std::string newLastLine = readLastLogLine("security_events.log");

    // إذا كان السطر الجديد مختلف عن السابق ويتضمن eventType والوصف => ناجح
    bool success = false;
    if (newLastLine != prevLastLine) {
        if (newLastLine.find(eventType) != std::string::npos &&
            newLastLine.find(description) != std::string::npos) {
            success = true;
        }
    }
    return success;
}

int main() {
    int passed = 0;
    int failed = 0;

    // اختبار 1
    if (testLogEvent("LOGIN", "User admin logged in")) {
        std::cout << "[PASS] Test 1: LOGIN event logged correctly.\n";
        ++passed;
    } else {
        std::cout << "[FAIL] Test 1: LOGIN event logging failed.\n";
        ++failed;
    }

    // اختبار 2
    if (testLogEvent("ERROR", "Failed to open database connection")) {
        std::cout << "[PASS] Test 2: ERROR event logged correctly.\n";
        ++passed;
    } else {
        std::cout << "[FAIL] Test 2: ERROR event logging failed.\n";
        ++failed;
    }

    // اختبار 3 (حالة وصف طويل)
    if (testLogEvent("WARNING", "Disk space low: less than 5% remaining")) {
        std::cout << "[PASS] Test 3: WARNING event logged correctly.\n";
        ++passed;
    } else {
        std::cout << "[FAIL] Test 3: WARNING event logging failed.\n";
        ++failed;
    }

    std::cout << "---------------------------\n";
    std::cout << "Passed: " << passed << "\nFailed: " << failed << "\n";

    if (failed == 0) {
        std::cout << "All tests passed successfully.\n";
        return 0;
    } else {
        std::cout << "Some tests failed. Check above details.\n";
        return 1;
    }
}
