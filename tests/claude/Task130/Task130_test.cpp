#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>
#include <curl/curl.h>  // لـ HTTP GET

#include "../../../source/output/claude/cpp/Task130_CLAUDE_claude-3-5-sonnet-20240620.cpp"

using namespace std;

// لجمع الرد من CURL
size_t writeCallback(void* contents, size_t size, size_t nmemb, string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

// انتظار السيرفر ليشتغل
void wait_for_server() {
    this_thread::sleep_for(chrono::seconds(1));
}
int main() {
    // شغّل السيرفر في ثريد مستقل
    thread server_thread([]() {
        crow_main();  // اسم جديد لدالة main من الحل
    });

    wait_for_server();  // أعطه وقت ليشتغل

    CURL* curl;
    CURLcode res;
    string response;
    long http_code = 0;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:8080/api/data");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3L);
        curl_easy_setopt(curl, CURLOPT_HEADER, 1L);  // للحصول على الهيدر

        res = curl_easy_perform(curl);

        if (res == CURLE_OK) {
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
            cout << "[INFO] HTTP code: " << http_code << endl;

            bool pass = true;

            if (http_code == 200 &&
                response.find("This is CORS-enabled data") != string::npos &&
                response.find("Access-Control-Allow-Origin: *") != string::npos) {
                cout << "[PASS] GET /api/data returns expected JSON and CORS headers.\n";
            } else {
                cout << "[FAIL] GET /api/data did not return expected content or headers.\n";
                cout << "[DEBUG] Response:\n" << response << endl;
            }

        } else {
            cout << "[FAIL] curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    // السيرفر رح يتم تنظيفه تلقائيًا لما البرنامج ينتهي
    server_thread.detach();  // نتركه ينتهي تلقائيًا
    return 0;
}
