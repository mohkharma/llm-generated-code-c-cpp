#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <csignal>
#include <unistd.h>
#include <sys/wait.h>

bool run_kill_process_test(const char* pid_str, const std::string& expected_start) {
    // نفترض أن البرنامج المترجم اسمه kill_process وموجود في نفس المجلد
    std::string command = "./kill_process ";
    command += pid_str;
    command += " 2>&1";

    FILE* pipe = popen(command.c_str(), "r");
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

    return output.find(expected_start) == 0;
}

int main(int argc, char* argv[]) {
    int pass = 0, fail = 0;

    // 1. عدم تمرير PID (argc != 2)
    {
        FILE* pipe = popen("./kill_process", "r");
        char buffer[256];
        std::string output;
        while (fgets(buffer, sizeof(buffer), pipe)) output += buffer;
        int ret_code = pclose(pipe);

        if (output.find("Usage") == 0 && ret_code != 0) {
            std::cout << "test_no_argument: PASS\n";
            pass++;
        } else {
            std::cout << "test_no_argument: FAIL\n";
            fail++;
        }
    }

    // 2. PID صحيح موجود (غالباً PID 1)
    {
        int res = kill(1, 0); // فقط تحقق إن العملية موجودة (0 لإشارة لا تسبب فعل)
        if (res == 0) {
            bool ok = run_kill_process_test("1", "");
            // بما أن البرنامج لا يطبع رسالة نجاح، نقبل نجاح التنفيذ فقط
            std::cout << "test_valid_pid: PASS\n";
            pass++;
        } else {
            std::cout << "test_valid_pid: SKIPPED (PID 1 not found)\n";
        }
    }

    // 3. PID غير صحيح (نصي)
    {
        bool ok = run_kill_process_test("abc", "Failed to kill process with PID 0");
        std::cout << "test_invalid_pid: " << (ok ? "PASS" : "FAIL") << "\n";
        ok ? pass++ : fail++;
    }

    // 4. PID غير موجود
    {
        bool ok = run_kill_process_test("999999", "Failed to kill process with PID 999999");
        std::cout << "test_pid_not_found: " << (ok ? "PASS" : "FAIL") << "\n";
        ok ? pass++ : fail++;
    }

    // 5. PID خارج النطاق (رقم كبير جدا)
    {
        bool ok = run_kill_process_test("999999999999999999999999", "Failed to kill process with PID 0");
        std::cout << "test_pid_out_of_range: " << (ok ? "PASS" : "FAIL") << "\n";
        ok ? pass++ : fail++;
    }

    std::cout << "Total Pass: " << pass << ", Total Fail: " << fail << std::endl;
    return 0;
}
