#include <iostream>
#include <sstream>
#include <string>

 #include "../../../source/output/gpt4o/cpp/Task132_OPENAI_gpt-4o.cpp"

// دالة مساعدة لاختبار سجل الأحداث
bool testLogging() {
    SecurityEventLogger logger;

    // تسجيل أحداث ثابتة
    logger.logEvent("User login successful");
    logger.logEvent("File accessed: confidential.txt");

    // التقاط الإخراج باستخدام stringstream
    std::ostringstream oss;
    std::streambuf* oldCoutBuf = std::cout.rdbuf(oss.rdbuf());

    logger.showEvents();

    // استرجاع تدفق cout
    std::cout.rdbuf(oldCoutBuf);

    std::string output = oss.str();

    // تحقق من وجود نصوص الأحداث في الإخراج
    bool pass = true;
    if (output.find("User login successful") == std::string::npos) pass = false;
    if (output.find("File accessed: confidential.txt") == std::string::npos) pass = false;

    // أيضاً تحقق من وجود طابع زمني (بصيغة "YYYY-MM-DD")
    if (output.find("-") == std::string::npos) pass = false;

    return pass;
}

int main() {
    if (testLogging()) {
        std::cout << "[PASS] SecurityEventLogger logs and shows events correctly.\n";
    } else {
        std::cout << "[FAIL] SecurityEventLogger test failed.\n";
    }

    return 0;
}
