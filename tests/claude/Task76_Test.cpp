#include <iostream>
#include <cstdio>
#include <string>

bool run_test(const std::string& test_name, const std::string& arg, const std::string& expected_start) {
    std::string cmd = "./http_title_fetcher " + arg + " 2>&1";  // نفترض اسم البرنامج المترجم
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) {
        std::cerr << "Failed to run command\n";
        return false;
    }

    char buffer[512];
    std::string output;
    while (fgets(buffer, sizeof(buffer), pipe)) {
        output += buffer;
    }
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

    // 1. عدم تمرير URL
    {
        FILE* pipe = popen("./http_title_fetcher 2>&1", "r");
        char buffer[512];
        std::string output;
        while (fgets(buffer, sizeof(buffer), pipe)) output += buffer;
        int ret = pclose(pipe);

        bool pass = (output.find("Usage") == 0) && (ret != 0);
        std::cout << "test_no_argument: " << (pass ? "PASS" : "FAIL") << std::endl;
        pass ? pass_count++ : fail_count++;
    }

    // 2. URL صحيح ومحتوي الصفحة يحوي <title>
    // مثال URL مشهور مع عنوان: https://www.example.com
    if (run_test("test_valid_url_with_title", "https://www.google.com/", "Page title: Example Domain")) pass_count++; else fail_count++;

    // 3. URL صحيح لكن لا عنوان <title> (مثال URL وهمي - نستخدم httpbin.org/html لكن فيه title)
    // صعب إيجاد صفحة بدون title بسهولة، نفترض اختبار عام على URL لا يجيب HTML صالح:
    if (run_test("test_valid_url_no_title", "https://httpbin.org/status/204", "Page title: No title found")) pass_count++; else fail_count++;

    // 4. URL خاطئ أو غير موجود
    if (run_test("test_invalid_url", "https://nonexistent.invalidurl", "Page title: Error:")) pass_count++; else fail_count++;

    std::cout << "Total Pass: " << pass_count << ", Total Fail: " << fail_count << std::endl;

    return 0;
}
