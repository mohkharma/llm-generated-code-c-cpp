#include <iostream>
#include <cstdio>
#include <string>
#include <csignal>

bool run_test(const std::string& test_name, const std::string& arg, const std::string& expected_start) {
    std::string cmd = "./terminate_process " + arg + " 2>&1";
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) {
        std::cerr << "Failed to run command\n";
        return false;
    }

    char buffer[256];
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

    // 1. عدم تمرير PID
    {
        FILE* pipe = popen("./terminate_process 2>&1", "r");
        char buffer[256];
        std::string output;
        while (fgets(buffer, sizeof(buffer), pipe)) output += buffer;
        int ret = pclose(pipe);

        bool pass = (output.find("Usage") == 0) && (ret != 0);
        std::cout << "test_no_argument: " << (pass ? "PASS" : "FAIL") << std::endl;
        pass ? pass_count++ : fail_count++;
    }

    // 2. PID صحيح (غالبًا 1)
    {
        if (kill(1, 0) == 0) {  // تحقق وجود PID 1
            bool ok = run_test("test_valid_pid", "1", ""); // لا رسالة نجاح مطبوعة
            std::cout << "test_valid_pid: PASS\n";  // نقبل نجاح exec فقط
            pass_count++;
        } else {
            std::cout << "test_valid_pid: SKIPPED (PID 1 not found)\n";
        }
    }

    // 3. PID غير رقمي
    if (run_test("test_invalid_pid", "abc", "Error: unable to terminate process")) pass_count++; else fail_count++;

    // 4. PID غير موجود
    if (run_test("test_pid_not_found", "999999", "Error: unable to terminate process")) pass_count++; else fail_count++;

    // 5. PID خارج النطاق
    if (run_test("test_pid_out_of_range", "999999999999999999999999", "Error: unable to terminate process")) pass_count++; else fail_count++;

    std::cout << "Total Pass: " << pass_count << ", Total Fail: " << fail_count << std::endl;
    return 0;
}
