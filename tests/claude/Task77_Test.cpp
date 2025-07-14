#include <iostream>
#include <cstdio>
#include <string>

bool run_test(const std::string& test_name, const std::string& args, const std::string& expected_start) {
    std::string cmd = "./ftp_downloader " + args + " 2>&1"; // برنامجك المترجم
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) {
        std::cerr << "Failed to run command\n";
        return false;
    }
    char buffer[512];
    std::string output;
    while (fgets(buffer, sizeof(buffer), pipe)) output += buffer;
    int ret_code = pclose(pipe);

    bool pass = (output.find(expected_start) == 0);
    std::cout << test_name << ": " << (pass ? "PASS" : "FAIL") << std::endl;

    if (!pass) {
        std::cout << "  Expected start: \"" << expected_start << "\"\n";
        std::cout << "  Got: \"" << output << "\"\n";
    }
    return pass;
}

int main() {
    int pass_count = 0, fail_count = 0;

    // 1. عدم تمرير 4 أرجومنتات (نجرب بدون أرجومنت أو أقل من 4)
    if (run_test("test_missing_args", "", "Usage:")) pass_count++; else fail_count++;

    // 2. تنزيل ناجح (اختبر باستخدام سيرفر FTP صالح لديك، هنا مثال وهمي)
    // غير صالح للاختبار الفعلي إلا مع سيرفر موجود
    // استبدل hostname و username و password و filename بقيم حقيقية للاختبار
    if (run_test("test_successful_download", "ftp.example.com user pass file.txt", "File file.txt downloaded successfully.")) pass_count++; else fail_count++;

    // 3. فشل التنزيل (مثلاً سيرفر غير موجود)
    if (run_test("test_failed_download", "invalid.host user pass file.txt", "Failed to download the file:")) pass_count++; else fail_count++;

    std::cout << "Total Pass: " << pass_count << ", Total Fail: " << fail_count << std::endl;
    return 0;
}
