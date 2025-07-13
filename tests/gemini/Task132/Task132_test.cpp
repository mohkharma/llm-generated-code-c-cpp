#include <iostream>
#include <fstream>
#include <filesystem>
#include <thread>
#include <chrono>

 #include "../../../source/output/gemini/cpp/Task132_GEMINI_gemini-1.5-pro-001.cpp"

namespace fs = std::filesystem;

// دالة مساعدة لكتابة نص في ملف (لتغيير الملف الذي نراقبه)
void modifyFile(const std::string& filename) {
    std::ofstream ofs(filename, std::ios::app);
    ofs << "Test modification at " << std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) << "\n";
    ofs.close();
}

// دالة مساعدة لقراءة آخر سطر من ملف اللوق
std::string readLastLogLine(const std::string& filename) {
    std::ifstream ifs(filename);
    std::string line, lastLine;
    while (std::getline(ifs, line)) {
        if (!line.empty()) lastLine = line;
    }
    return lastLine;
}

int main() {
    const std::string testFile = "file_to_monitor.txt";
    const std::string logFile = "security_events.log";

    // تأكد أن الملف موجود قبل الاختبار
    {
        std::ofstream ofs(testFile, std::ios::app);
        ofs.close();
    }

    // احذف ملف اللوق القديم إن وجد (للتأكد من نتائج نظيفة)
    if (fs::exists(logFile)) {
        fs::remove(logFile);
    }

    // شغّل مراقبة الملف في Thread منفصل (تعمل حلقة لا نهائية)
    std::thread monitorThread(monitor_file_changes, testFile);

    // انتظر ثانية لتبدأ المراقبة
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // عدّل الملف ليتعرف البرنامج على تغيير
    modifyFile(testFile);

    // انتظر 7 ثواني (مدة أكثر من 5 ثواني لتمرير دورة الانتظار داخل المراقب)
    std::this_thread::sleep_for(std::chrono::seconds(7));

    // اقرأ آخر سطر من ملف اللوق للتحقق
    std::string lastLogLine = readLastLogLine(logFile);

    // تحقق وجود نص "File Change Detected" في السطر الأخير
    if (lastLogLine.find("File Change Detected") != std::string::npos) {
        std::cout << "[PASS] File change event logged successfully.\n";
    } else {
        std::cout << "[FAIL] File change event NOT logged.\n";
    }

    // بما أن المراقبة حلقة لا نهائية، ننهي البرنامج فجأة (غير نظيف لكن مناسب للاختبار)
    std::exit(0);
}
