#include <iostream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

bool fetch_json_and_print(const std::string& url, bool print_output = true) {
    CURL* curl = curl_easy_init();
    if (!curl) {
        if(print_output) std::cerr << "Failed to init cURL\n";
        return false;
    }

    std::string readBuffer;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        if(print_output) std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        return false;
    }

    try {
        auto json = nlohmann::json::parse(readBuffer);
        if(print_output) std::cout << json.dump(4) << std::endl;
        return true;
    } catch (nlohmann::json::parse_error& e) {
        if(print_output) std::cerr << "JSON parse error: " << e.what() << std::endl;
        return false;
    }
}

void test_valid_url() {
    std::string url = "https://auth.lambdatest.com/api/country-details";
    bool success = fetch_json_and_print(url, false);
    if(success) std::cout << "Test case valid URL: PASS\n";
    else std::cout << "Test case valid URL: FAIL\n";
}

void test_invalid_url() {
    std::string url = "https://invalid.url.fake/json";
    bool success = fetch_json_and_print(url, false);
    if(!success) std::cout << "Test case invalid URL: PASS\n";
    else std::cout << "Test case invalid URL: FAIL\n";
}

void test_malformed_json() {
    // مثال URL يرجع نص HTML وليس JSON
    std::string url = "https://www.example.com";
    bool success = fetch_json_and_print(url, false);
    if(!success) std::cout << "Test case malformed JSON: PASS\n";
    else std::cout << "Test case malformed JSON: FAIL\n";
}

int main(int argc, char* argv[]) {
    if (argc == 2) {
        // إذا أعطي رابط من السطر الأوامر، استعمله مثل برنامجك الأصلي
        if(!fetch_json_and_print(argv[1])) {
            return 1;
        }
        return 0;
    }

    // بدون أي وسيط، نفذ التستات بالترتيب
    test_valid_url();
    test_invalid_url();
    test_malformed_json();

    return 0;
}
