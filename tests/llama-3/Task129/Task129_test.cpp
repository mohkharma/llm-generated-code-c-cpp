#include "../../../source/output/llama-3/cpp/Task129_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"

#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sstream>

using namespace std;

// سيرفر صغير في الخلفية
void start_mock_server() {
    thread([]() {
        int server_fd = socket(AF_INET, SOCK_STREAM, 0);
        sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_port = htons(12345);
        addr.sin_addr.s_addr = INADDR_ANY;

        bind(server_fd, (sockaddr*)&addr, sizeof(addr));
        listen(server_fd, 1);

        while (true) {
            int client_fd = accept(server_fd, nullptr, nullptr);
            if (client_fd < 0) continue;

            char filename_buf[1024] = {0};
            recv(client_fd, filename_buf, sizeof(filename_buf), 0);
            string requested_file(filename_buf);

            ifstream file(requested_file, ios::binary);
            if (!file.is_open()) {
                close(client_fd);
                continue;
            }

            char buffer[1024];
            while (file.read(buffer, sizeof(buffer)) || file.gcount() > 0) {
                send(client_fd, buffer, file.gcount(), 0);
            }

            file.close();
            close(client_fd);
        }
    }).detach();

    this_thread::sleep_for(chrono::seconds(1)); // امنح السيرفر وقت للبدء
}

// إنشاء ملف موجود للاختبار
void create_test_file() {
    ofstream f("testFile.txt");
    f << "Hello from socket test!\n";
    f.close();
}

// دالة تقييم نتيجة الاختبار
void run_test(const string& test_name, const string& filename, bool expected_to_exist) {
    remove(filename.c_str());

    stringstream output;
    streambuf* orig_cout = cout.rdbuf();
    cout.rdbuf(output.rdbuf());

    retrieveFile(filename);

    cout.rdbuf(orig_cout);

    bool file_saved = ifstream(filename).good();
    if (file_saved) remove(filename.c_str());

    bool pass = (file_saved == expected_to_exist);

    if (pass) {
        cout << "[PASS] " << test_name << endl;
    } else {
        cout << "[FAIL] " << test_name << endl;
        cout << "  ⮕ Expected file saved: " << (expected_to_exist ? "Yes" : "No") << ", got: " << (file_saved ? "Yes" : "No") << endl;
        cout << "  ⮕ Output: " << output.str();
    }
}

int main() {
    create_test_file();
    start_mock_server();

    run_test("Retrieve existing file", "testFile.txt", true);
    run_test("Retrieve missing file", "notfound.txt", false);

    return 0;
}
