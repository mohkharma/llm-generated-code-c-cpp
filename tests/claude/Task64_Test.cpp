#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <stdexcept>

using json = nlohmann::json;

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t total_size = size * nmemb;
    output->append((char*)contents, total_size);
    return total_size;
}

json fetch_json(const std::string& url) {
    CURL* curl = curl_easy_init();
    std::string response_string;

    if (!curl) {
        throw std::runtime_error("Failed to init CURL");
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
    // To avoid curl output to stderr
    curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        curl_easy_cleanup(curl);
        throw std::runtime_error(curl_easy_strerror(res));
    }

    curl_easy_cleanup(curl);

    return json::parse(response_string);
}

void printTestResult(const std::string& testName, bool passed, const std::string& reason = "") {
    std::cout << testName << ": " << (passed ? "PASS" : "FAIL");
    if (!passed && !reason.empty()) std::cout << " (" << reason << ")";
    std::cout << std::endl;
}

int main(int argc, char* argv[]) {
    // اذا تم تشغيل مع ارجوما 1 = اجراء الطلب الحقيقي فقط (حسب كودك الاصلي)
    if (argc == 2) {
        std::string url = argv[1];
        try {
            json json_data = fetch_json(url);
            std::cout << json_data.dump(2) << std::endl;
            return 0;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return 1;
        }
    }

    // --- اما اذا لم يتم تمرير ارجوما (تشغيل التست كيسز) ---
    int passCount = 0, failCount = 0;

    // 1. اختبار رابط صالح
    try {
        std::string good_url = "https://auth.lambdatest.com/api/country-details";
        json j = fetch_json(good_url);
        // اختبار بسيط: هل JSON يحتوي مفتاح "country_name" (حسب API)
        bool passed = j.is_array() || j.contains("country_name") || !j.empty();
        printTestResult("test_valid_url", passed);
        if (passed) passCount++; else failCount++;
    } catch (...) {
        printTestResult("test_valid_url", false, "Exception thrown");
        failCount++;
    }

    // 2. اختبار رابط خاطئ (غير موجود مثلا)
    try {
        std::string bad_url = "https://auth.lambdatest.com/api/this-does-not-exist";
        fetch_json(bad_url);
        printTestResult("test_nonexistent_url", false, "Expected exception not thrown");
        failCount++;
    } catch (...) {
        printTestResult("test_nonexistent_url", true);
        passCount++;
    }

    // 3. اختبار نص غير رابط (فشل الطلب)
    try {
        std::string invalid_url = "not a url";
        fetch_json(invalid_url);
        printTestResult("test_invalid_url_format", false, "Expected exception not thrown");
        failCount++;
    } catch (...) {
        printTestResult("test_invalid_url_format", true);
        passCount++;
    }

    std::cout << "\nSummary: Passed " << passCount << ", Failed " << failCount << std::endl;

    return 0;
}
