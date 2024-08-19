#include <iostream>
#include <string>
#include <curl/curl.h>
#include <regex>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: ./main <URL>" << std::endl;
        return 1;
    }

    std::string url = argv[1];
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        /* always clean up */
        curl_easy_cleanup(curl);

        std::regex titleRegex("<title>(.*?)</title>");
        std::smatch match;
        if (std::regex_search(readBuffer, match, titleRegex) && match.size() > 1) {
            std::string title = match.str(1);
            std::cout << title << std::endl;
        }
    }

    curl_global_cleanup();
    return 0;
}