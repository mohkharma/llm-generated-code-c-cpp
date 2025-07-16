#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// cURL write callback to store response in std::string
size_t writeCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t totalSize = size * nmemb;
    ((std::string*)userp)->append((char*)contents, totalSize);
    return totalSize;
}

// جلب JSON من URL
json fetch_json(const std::string& url) {
    CURL* curl = curl_easy_init();
    std::string responseBuffer;

    if (!curl) throw std::runtime_error("Error initializing cURL");

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseBuffer);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        throw std::runtime_error(std::string("Error fetching URL: ") + curl_easy_strerror(res));
    }

    try {
        return json::parse(responseBuffer);
    } catch (json::parse_error& e) {
        throw std::runtime_error(std::string("JSON parse error: ") + e.what());
    }
}

// اختبار النجاح على URL حقيقي
void test_valid_url() {
    try {
        std::string url = "https://auth.lambdatest.com/api/country-details";
        json result = fetch_json(url);
        if (!result.empty()) {
            std::cout << "Test case valid URL: PASS\n";
        } else {
            std::cout << "Test case valid URL: FAIL (empty JSON)\n";
        }
    } catch (const std::exception& e) {
        std::cout << "Test case valid URL: FAIL (" << e.what() << ")\n";
    }
}

// اختبار خطأ بسبب URL خاطئ
void test_invalid_url() {
    try {
        std::string url = "https://invalid.url.fake/json";
        json result = fetch_json(url);
        std::cout << "Test case invalid URL: FAIL (expected exception but got JSON)\n";
    } catch (...) {
        std::cout << "Test case invalid URL: PASS\n";
    }
}

// اختبار خطأ بسبب JSON غير صالح (باستخدام URL يعيد نص غير JSON)
void test_malformed_json() {
    try {
        // يمكن استبدال هذا URL بشيء يعيد نص غير JSON
        std::string url = "https://www.example.com"; // موقع يعطي html وليس json
        json result = fetch_json(url);
        std::cout << "Test case malformed JSON: FAIL (expected parse error)\n";
    } catch (...) {
        std::cout << "Test case malformed JSON: PASS\n";
    }
}

int main(int argc, char* argv[]) {
    // لو تم تمرير رابط، نطبعه فقط (مثل البايثون)
    if (argc == 2) {
        try {
            json j = fetch_json(argv[1]);
            std::cout << j.dump(2) << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return 1;
        }
        return 0;
    }

    // بدون args: نفذ التستات
    test_valid_url();
    test_invalid_url();
    test_malformed_json();

    return 0;
}
