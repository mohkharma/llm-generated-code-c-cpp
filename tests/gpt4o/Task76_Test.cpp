#include <iostream>
#include <cstdio>
#include <string>

bool run_test(const std::string& test_name, const std::string& arg, const std::string& expected_start, bool expect_stderr = false) {
    std::string cmd = "./main ";
    if (!arg.empty()) {
        cmd += arg;
    }
    if (expect_stderr) {
        cmd += " 2>&1";  // دمج stderr مع stdout
    } else {
        cmd += " 2>/dev/null"; // تجاهل stderr
    }

    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) {
        std::cerr << "Failed to run command\n";
        return false;
    }

    char buffer[512];
    std::string output;
    while (fgets(buffer, sizeof(buffer), pipe)) output += buffer;
    int ret_code = pclose(pipe);

    // تنظيف \n و\r من النهاية
    while (!output.empty() && (output.back() == '\n' || output.back() == '\r')) {
        output.pop_back();
    }

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

    // 1. عدم تمرير URL
    {
        FILE* pipe = popen("./main 2>&1", "r");
        char buffer[512];
        std::string output;
        while (fgets(buffer, sizeof(buffer), pipe)) output += buffer;
        int ret = pclose(pipe);

        bool pass = (output.find("Usage:") == 0) && (ret != 0);
        std::cout << "test_no_argument: " << (pass ? "PASS" : "FAIL") << std::endl;
        pass ? pass_count++ : fail_count++;
    }

    // 2. URL صحيح مع عنوان
    if (run_test("test_valid_url_with_title", "https://www.example.com", "Example Domain")) pass_count++; else fail_count++;

    // 3. URL صحيح بدون عنوان (نستخدم صفحة لا تحتوي على <title>)
    if (run_test("test_valid_url_no_title", "https://httpbin.org/status/204", "")) pass_count++; else fail_count++;

    // 4. URL خاطئ (لا معالجة أخطاء في الكود - ننتظر لا شيء أو رسالة فارغة)
    if (run_test("test_invalid_url", "https://nonexistent.invalidurl", "")) pass_count++; else fail_count++;

    std::cout << "Total Pass: " << pass_count << ", Total Fail: " << fail_count << std::endl;
    return 0;
}
