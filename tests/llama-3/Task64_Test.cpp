#include <iostream>
#include <string>
#include <json/json.h>
#include <curl/curl.h>

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

Json::Value readJsonFromUrl(std::string url) {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            std::cerr << "cURL error: " << curl_easy_strerror(res) << std::endl;
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    Json::Value json;
    Json::CharReaderBuilder builder;
    std::string errs;
    std::istringstream s(readBuffer);
    if (!Json::parseFromStream(builder, s, &json, &errs)) {
        std::cerr << "JSON parse error: " << errs << std::endl;
        json.clear();
    }
    return json;
}

// Helper to check if JSON is empty (fail to parse)
bool isJsonEmpty(const Json::Value &json) {
    return json.isNull() || json.empty();
}

void test_valid_url() {
    std::string url = "https://auth.lambdatest.com/api/country-details";
    Json::Value json = readJsonFromUrl(url);
    if (!isJsonEmpty(json))
        std::cout << "Test case valid URL: PASS\n";
    else
        std::cout << "Test case valid URL: FAIL\n";
}

void test_invalid_url() {
    std::string url = "https://invalid.url.fake/json";
    Json::Value json = readJsonFromUrl(url);
    if (isJsonEmpty(json))
        std::cout << "Test case invalid URL: PASS\n";
    else
        std::cout << "Test case invalid URL: FAIL\n";
}

void test_malformed_json() {
    // URL that returns HTML or non-JSON content
    std::string url = "https://www.example.com";
    Json::Value json = readJsonFromUrl(url);
    if (isJsonEmpty(json))
        std::cout << "Test case malformed JSON: PASS\n";
    else
        std::cout << "Test case malformed JSON: FAIL\n";
}

int main(int argc, char *argv[]) {
    if (argc == 2) {
        Json::Value json = readJsonFromUrl(argv[1]);
        std::cout << json << std::endl;
        return 0;
    }

    // Run tests if no argument provided
    test_valid_url();
    test_invalid_url();
    test_malformed_json();

    return 0;
}
