#include "../../source/output/claude/cpp/Task43_CLAUDE_claude-3-5-sonnet-20240620.cpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <curl/curl.h>

int passed = 0, failed = 0;

void print_result(const std::string& name, bool ok) {
    std::cout << (ok ? "[PASS] " : "[FAIL] ") << name << "\n";
    (ok ? passed : failed)++;
}

std::string response_data;
size_t write_callback(void* contents, size_t size, size_t nmemb, void*) {
    response_data.append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string send_post(const std::string& url, const std::string& body, std::string& cookie_out, long& status_code) {
    response_data.clear();
    CURL* curl = curl_easy_init();
    if (!curl) {
        status_code = 0;
        return "CURL init failed";
    }

    struct curl_slist* headers = curl_slist_append(nullptr, "Content-Type: application/json");

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "");

    // ✅ تمرير cookie_out بشكل آمن
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &cookie_out);
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, [](char* buffer, size_t size, size_t nitems, void* userdata) -> size_t {
        std::string header(buffer, size * nitems);
        if (header.find("Set-Cookie:") != std::string::npos) {
            size_t start = header.find("session_id=");
            if (start != std::string::npos) {
                size_t end = header.find(";", start);
                std::string* out = static_cast<std::string*>(userdata);
                *out = header.substr(start, end - start);
            }
        }
        return size * nitems;
    });

    curl_easy_perform(curl);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status_code);

    curl_slist_free_all(headers);  // ✅ تنظيف headers
    curl_easy_cleanup(curl);
    return response_data;
}


std::string send_get(const std::string& url, const std::string& cookie, long& status_code) {
    response_data.clear();
    CURL* curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    if (!cookie.empty()) {
        curl_easy_setopt(curl, CURLOPT_COOKIE, cookie.c_str());
    }
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_perform(curl);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status_code);
    curl_easy_cleanup(curl);
    return response_data;
}

void run_tests() {
    std::string base = "http://localhost:8080";
    long code;
    std::string cookie;

    send_post(base + "/register", R"({"username":"ali","password":"123"})", cookie, code);
    print_result("Register new user", code == 201);

    send_post(base + "/register", R"({"username":"ali","password":"123"})", cookie, code);
    print_result("Register duplicate user", code == 400);

    send_post(base + "/login", R"({"username":"ali","password":"123"})", cookie, code);
    print_result("Login with valid credentials", code == 200 && !cookie.empty());

    send_get(base + "/protected", cookie, code);
    print_result("Access protected route (authorized)", code == 200 && response_data.find("ali") != std::string::npos);

    send_post(base + "/logout", "{}", cookie, code);
    send_get(base + "/protected", cookie, code);
    print_result("Access protected after logout", code == 401);
}

int main() {
    std::thread server_thread([]() {
        start_server();  // 🟢 من ملف الحل الأصلي
    });

    std::this_thread::sleep_for(std::chrono::seconds(2));  // ⏳ انتظار لتشغيل الخادم

    run_tests();

    std::cout << "\nSummary: " << passed << " passed, " << failed << " failed.\n";
    std::exit(failed == 0 ? 0 : 1);
}
