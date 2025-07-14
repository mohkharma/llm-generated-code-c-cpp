#include <iostream>
#include <string>
#include <curl/curl.h>
#include <fstream>
#include <cstdio>

size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream) {
    std::ostream &os = *static_cast<std::ostream*>(stream);
    os.write(static_cast<char*>(ptr), size * nmemb);
    return size * nmemb;
}

int main() {
    std::string url;
    std::cout << "Enter the URL of the EXE file: ";
    std::cin >> url;
    std::string filename = url.substr(url.find_last_of('/') + 1);
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open file for writing" << std::endl;
        std::cout << "Test case 1 result: FAIL" << std::endl;
        return 1;
    }

    CURL *curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &file);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        file.close();

        if(res != CURLE_OK) {
            std::cerr << "cURL error: " << curl_easy_strerror(res) << std::endl;
            std::cout << "Test case 1 result: FAIL" << std::endl;
            curl_global_cleanup();
            return 1;
        }

        // تحقق وجود الملف
        FILE* checkFile = fopen(filename.c_str(), "rb");
        if(checkFile) {
            fclose(checkFile);
            std::cout << "Test case 1 result: PASS" << std::endl;
            // تنفيذ الملف
            std::system(filename.c_str());
        } else {
            std::cout << "Test case 1 result: FAIL" << std::endl;
            curl_global_cleanup();
            return 1;
        }
    } else {
        std::cout << "Test case 1 result: FAIL" << std::endl;
        curl_global_cleanup();
        return 1;
    }

    curl_global_cleanup();
    return 0;
}
// URL: https://download.sysinternals.com/files/ProcessExplorer.exe