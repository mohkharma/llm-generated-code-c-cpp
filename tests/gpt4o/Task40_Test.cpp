#include "../../source/output/gpt4o/cpp/Task40_OPENAI_gpt-4o.cpp"  // Include the implementation

#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <chrono>
#include <cppcms/service.h>
#include <cppcms/applications_pool.h>
#include <cppcms/http_client.h>
#include <cppcms/json.h>

int tests_passed = 0;
int tests_failed = 0;

void print_result(const std::string &test_name, bool passed) {
    if (passed) {
        std::cout << "[PASS] " << test_name << "\n";
        tests_passed++;
    } else {
        std::cout << "[FAIL] " << test_name << "\n";
        tests_failed++;
    }
}

// ✅ Thread لتشغيل السيرفر
void run_server() {
    const char *argv[] = {"app", "-c", "settings.json"};
    int argc = sizeof(argv) / sizeof(argv[0]);
    cppcms::service srv(argc, const_cast<char**>(argv));
    srv.applications_pool().mount(cppcms::applications_factory<settings>());
    srv.run();
}

// ✅ اختبار إرسال POST مع CSRF صحيح
void test_valid_csrf() {
    try {
        cppcms::http::client client("http://localhost:8080");

        // GET request to get CSRF token
        cppcms::http::request get_req;
        get_req.method("GET");
        get_req.path_info("/settings");

        cppcms::http::response get_res = client.request(get_req);
        std::string body = get_res.load_text();

        std::string token;
        size_t pos = body.find("name='_csrf_token' value='");
        if (pos != std::string::npos) {
            size_t start = pos + 26;
            size_t end = body.find("'", start);
            token = body.substr(start, end - start);
        }

        if (token.empty()) {
            print_result("test_valid_csrf", false);
            return;
        }

        // POST request with valid CSRF
        cppcms::http::request post_req;
        post_req.method("POST");
        post_req.path_info("/settings");
        post_req.content_type("application/x-www-form-urlencoded");
        std::ostringstream post_data;
        post_data << "_csrf_token=" << token << "&username=testuser";
        post_req.load(post_data.str());

        cppcms::http::response post_res = client.request(post_req);
        std::string post_body = post_res.load_text();
        print_result("test_valid_csrf", post_body.find("Settings updated!") != std::string::npos);
    } catch (...) {
        print_result("test_valid_csrf", false);
    }
}

// ❌ اختبار إرسال POST بدون CSRF
void test_missing_csrf() {
    try {
        cppcms::http::client client("http://localhost:8080");

        cppcms::http::request post_req;
        post_req.method("POST");
        post_req.path_info("/settings");
        post_req.content_type("application/x-www-form-urlencoded");
        post_req.load("username=testuser");

        cppcms::http::response post_res = client.request(post_req);
        std::string post_body = post_res.load_text();
        print_result("test_missing_csrf", post_body.find("CSRF token is missing") != std::string::npos);
    } catch (...) {
        print_result("test_missing_csrf", false);
    }
}

int main() {
    // 🔸 تشغيل السيرفر في Thread منفصل
    std::thread server_thread(run_server);
    std::this_thread::sleep_for(std::chrono::seconds(2)); // ⏳ انتظر حتى يعمل السيرفر

    // 🧪 نفّذ الاختبارات
    test_valid_csrf();
    test_missing_csrf();

    // ✅ اطبع النتيجة النهائية
    std::cout << "\nTests passed: " << tests_passed << "\n";
    std::cout << "Tests failed: " << tests_failed << "\n";

    // لا نوقف السيرفر هنا لأن cppcms::service لا يدعم الإنهاء اليدوي بسهولة
    // في الاستخدام العملي، افصل العملية بعد الاختبار
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return 0;
}
