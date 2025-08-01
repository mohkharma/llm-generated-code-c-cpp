#include <iostream>
#include <thread>
#include <chrono>
#include <curl/curl.h>

#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/registry.hpp>
#include <xmlrpc-c/server_abyss.hpp>

// --------------------- السيرفر -----------------------

class addMethod : public xmlrpc_c::method {
public:
    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value* const retvalP) {
        int const x(paramList.getInt(0));
        int const y(paramList.getInt(1));
        paramList.verifyEnd(2);
        *retvalP = xmlrpc_c::value_int(x + y);
    }
};

class subtractMethod : public xmlrpc_c::method {
public:
    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value* const retvalP) {
        int const x(paramList.getInt(0));
        int const y(paramList.getInt(1));
        paramList.verifyEnd(2);
        *retvalP = xmlrpc_c::value_int(x - y);
    }
};

void run_server() {
    xmlrpc_c::registry myRegistry;
    myRegistry.addMethod("add", new addMethod);
    myRegistry.addMethod("subtract", new subtractMethod);

    xmlrpc_c::serverAbyss myServer(
        xmlrpc_c::serverAbyss::constrOpt()
            .registryP(&myRegistry)
            .portNumber(8000)
            .logFileName("xmlrpc_log.txt")
    );

    std::cout << "🚀 Server running on port 8000...\n";
    myServer.run();
}

// --------------------- اختبار العميل -----------------------

int tests_passed = 0;
int tests_failed = 0;

void print_result(const std::string& name, bool passed) {
    if (passed) {
        std::cout << "[PASS] " << name << "\n";
        tests_passed++;
    } else {
        std::cout << "[FAIL] " << name << "\n";
        tests_failed++;
    }
}

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string call_xmlrpc(const std::string& method, int a, int b) {
    CURL* curl = curl_easy_init();
    std::string response;

    std::string payload =
        "<?xml version=\"1.0\"?>"
        "<methodCall><methodName>" + method + "</methodName><params>"
        "<param><value><int>" + std::to_string(a) + "</int></value></param>"
        "<param><value><int>" + std::to_string(b) + "</int></value></param>"
        "</params></methodCall>";

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:8000/RPC2");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curl_slist_append(nullptr, "Content-Type: text/xml"));
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }

    return response;
}

bool contains_result(const std::string& response, int expected) {
    std::string tag = "<int>" + std::to_string(expected) + "</int>";
    return response.find(tag) != std::string::npos;
}

// اختبارات add
void test_add_1() { print_result("test_add_1", contains_result(call_xmlrpc("add", 2, 3), 5)); }
void test_add_2() { print_result("test_add_2", contains_result(call_xmlrpc("add", -2, -3), -5)); }
void test_add_3() { print_result("test_add_3", contains_result(call_xmlrpc("add", 100, 0), 100)); }
void test_add_4() { print_result("test_add_4", contains_result(call_xmlrpc("add", 1000000, 1), 1000001)); }
void test_add_5() { print_result("test_add_5", contains_result(call_xmlrpc("add", -50, 100), 50)); }

// اختبارات subtract
void test_sub_1() { print_result("test_sub_1", contains_result(call_xmlrpc("subtract", 5, 2), 3)); }
void test_sub_2() { print_result("test_sub_2", contains_result(call_xmlrpc("subtract", 0, 0), 0)); }
void test_sub_3() { print_result("test_sub_3", contains_result(call_xmlrpc("subtract", -5, -5), 0)); }
void test_sub_4() { print_result("test_sub_4", contains_result(call_xmlrpc("subtract", 3, 10), -7)); }
void test_sub_5() { print_result("test_sub_5", contains_result(call_xmlrpc("subtract", 100000, 99999), 1)); }

int main() {
    std::thread server_thread(run_server);  // تشغيل الخادم في خيط منفصل
    std::this_thread::sleep_for(std::chrono::seconds(1));  // انتظار الخادم ليشتغل

    // تشغيل الاختبارات
    test_add_1();
    test_add_2();
    test_add_3();
    test_add_4();
    test_add_5();
    test_sub_1();
    test_sub_2();
    test_sub_3();
    test_sub_4();
    test_sub_5();

    std::cout << "\n✅ Total Passed: " << tests_passed << "\n";
    std::cout << "❌ Total Failed: " << tests_failed << "\n";

    std::exit(tests_failed == 0 ? 0 : 1);  // إنهاء البرنامج (سيوقف السيرفر)
}
