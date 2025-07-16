#include <curl/curl.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

int main(void) {
    CURL *curl;
    FILE *fp;
    CURLcode res;
    const char *url = "https://download.sysinternals.com/files/ProcessExplorer.exe";
    const char *filename = "program.exe";

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        fp = fopen(filename, "wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);

        fclose(fp);

        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            std::cout << "Test case 1 result: FAIL" << std::endl;
        } else {
            // تحقق أن الملف تم تنزيله بنجاح
            FILE* checkFile = fopen(filename, "rb");
            if(checkFile) {
                fclose(checkFile);
                std::cout << "Test case 1 result: PASS" << std::endl;
                // تنفيذ الملف
                system(filename);
            } else {
                std::cout << "Test case 1 result: FAIL" << std::endl;
            }
        }

        curl_easy_cleanup(curl);
    } else {
        std::cout << "Test case 1 result: FAIL" << std::endl;
    }
    curl_global_cleanup();

    return 0;
}
