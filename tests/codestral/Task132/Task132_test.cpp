#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>

// تضمين ملف الحل فقط، لا تعدل مسار الملف هذا حسب موقعك
#include "../../../source/output/codestral/cpp/Task132_MISTRAL_codestral-latest.cpp"

// دالة مساعدة لقراءة حجم ملف
std::streampos getFileSize(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file.is_open()) return 0;
    return file.tellg();
}

int main() {
    const std::string logFilename = "security.log";

    // احصل على حجم الملف قبل تشغيل الدالة
    std::streampos sizeBefore = getFileSize(logFilename);

    // شغّل دالة تسجيل الأحداث في Thread منفصل
    std::thread loggerThread(logSecurityEvents);

    // انتظر 3 ثواني لكي يسجل البرنامج أحداث
    std::this_thread::sleep_for(std::chrono::seconds(3));

    // تحقق من حجم الملف بعد فترة الانتظار
    std::streampos sizeAfter = getFileSize(logFilename);

    // طباعة النتيجة
    if (sizeAfter > sizeBefore) {
        std::cout << "[PASS] security.log file was updated with new events.\n";
    } else {
        std::cout << "[FAIL] security.log file was NOT updated.\n";
    }

    std::exit(0);

    return 0;
}
