#include <iostream>
#include <fstream>
#include <curl/curl.h>
#include <cstdlib>
#include <cstdio>

using namespace std;

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

int main() {
    string url = "https://download.sysinternals.com/files/ProcessExplorer.exe";
    string filename = "downloaded_program.exe";
    CURL *curl;
    FILE *fp;
    CURLcode res;
    curl = curl_easy_init();
    if (curl) {
        fp = fopen(filename.c_str(), "wb");
        if (!fp) {
            cerr << "Failed to open file for writing" << endl;
            cout << "Test case 1 result: FAIL" << endl;
            curl_easy_cleanup(curl);
            return 1;
        }
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);

        if (res != CURLE_OK) {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
            cout << "Test case 1 result: FAIL" << endl;
            return 1;
        }

        // تحقق وجود الملف
        FILE* checkFile = fopen(filename.c_str(), "rb");
        if (checkFile) {
            fclose(checkFile);
            cout << "Test case 1 result: PASS" << endl;
            // تنفيذ الملف
            system(filename.c_str());
        } else {
            cout << "Test case 1 result: FAIL" << endl;
            return 1;
        }
    } else {
        cout << "Test case 1 result: FAIL" << endl;
        return 1;
    }
    return 0;
}
