#include "../../../source/output/gemini/cpp/Task129_GEMINI_gemini-1.5-pro-001.cpp"


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <thread>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <csignal>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

// 🚀 شغل سيرفر python3 محلي على port 8000
pid_t start_test_server() {
    pid_t pid = fork();
    if (pid == 0) {
        execlp("python3", "python3", "-m", "http.server", "8000", nullptr);
        exit(1);
    }
    this_thread::sleep_for(chrono::seconds(2)); // انتظر السيرفر يشتغل
    return pid;
}

// 🛑 أوقف السيرفر
void stop_test_server(pid_t pid) {
    kill(pid, SIGTERM);
    waitpid(pid, nullptr, 0);
}

// ✍️ أنشئ ملف اختبار
void create_test_file() {
    ofstream file("testFile.txt");
    file << "Hello from server!" << endl;
    file.close();
}

// 🧪 اختبار
void run_test(const string& test_name, const string& filename, const string& url, bool expected_success) {
    remove(filename.c_str());

    stringstream output;
    streambuf* orig_cout = cout.rdbuf();
    streambuf* orig_cerr = cerr.rdbuf();
    cout.rdbuf(output.rdbuf());
    cerr.rdbuf(output.rdbuf());

    bool result = download_file(url, filename);

    cout.rdbuf(orig_cout);
    cerr.rdbuf(orig_cerr);

    string captured = output.str();

    bool file_exists = ifstream(filename).good();
    if (file_exists) remove(filename.c_str());

    bool pass = (result == expected_success) && (file_exists == expected_success);

    if (pass) {
        cout << "[PASS] " << test_name << endl;
    } else {
        cout << "[FAIL] " << test_name << endl;
        cout << "  ⮕ Output: " << captured;
        cout << "  ⮕ Expected success: " << (expected_success ? "true" : "false") << ", got: " << (result ? "true" : "false") << endl;
        cout << "  ⮕ File saved? " << (file_exists ? "Yes" : "No") << endl;
    }
}

int main() {
    create_test_file();
    pid_t server_pid = start_test_server();

    run_test("Download existing file", "testFile.txt", "http://127.0.0.1:8000/testFile.txt", true);
    run_test("Download missing file", "notfound.txt", "http://127.0.0.1:8000/notfound.txt", false);

    stop_test_server(server_pid);
    return 0;
}
