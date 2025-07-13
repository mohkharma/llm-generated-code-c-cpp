#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>

int passed = 0, failed = 0;

void start_test_server() {
    // أنشئ ملف HTML مؤقت
    std::ofstream file("existing.html");
    file << "<html><body><h1>Hello World</h1></body></html>";
    file.close();
}

pid_t launch_server() {
    pid_t pid = fork();
    if (pid == 0) {
        execlp("python3", "python3", "-m", "http.server", "8000", NULL);
        std::exit(1);  // إذا فشل execlp
    }
    sleep(1);  // انتظر السيرفر يشتغل
    return pid;
}

void stop_test_server(pid_t pid) {
    kill(pid, SIGTERM);
    waitpid(pid, nullptr, 0);
    std::remove("existing.html");
}

std::string run_curl(const std::string& url) {
    std::string command = "curl -s -o temp_output.txt -w \"%{http_code}\" \"" + url + "\"";
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) return "";

    char buffer[128];
    std::string result;
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }
    pclose(pipe);

    std::ifstream inFile("temp_output.txt");
    std::stringstream contents;
    contents << inFile.rdbuf();
    inFile.close();
    std::remove("temp_output.txt");

    return result;
}

void assertContains(const std::string& output, const std::string& expected, const std::string& testName) {
    if (output.find(expected) != std::string::npos) {
        std::cout << "الاختبار [" << testName << "] نجح ✅ يا آنسة مدجت!\n";
        passed++;
    } else {
        std::cout << "الاختبار [" << testName << "] فشل ❌ يا آنسة مدجت!\n";
        failed++;
    }
}

int main() {
    start_test_server();
    pid_t serverPid = launch_server();

    // اختبار جلب ملف موجود
    std::string result1 = run_curl("http://localhost:8000/existing.html");
    assertContains(result1, "Hello World", "Fetch existing file");

    // اختبار جلب ملف غير موجود
    std::string result2 = run_curl("http://localhost:8000/missing.html");
    assertContains(result2, "404", "Fetch missing file");

    stop_test_server(serverPid);

    std::cout << "\n=== TEST SUMMARY ===\n";
    std::cout << "Passed: " << passed << "\n";
    std::cout << "Failed: " << failed << "\n";

    return failed == 0 ? 0 : 1;
}
