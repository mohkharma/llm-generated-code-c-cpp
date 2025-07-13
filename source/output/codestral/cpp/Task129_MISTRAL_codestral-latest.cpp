// CPP
#include <cstring>
#include <iostream>
#include <string>
#include <fstream>
#include <curl/curl.h>

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    std::ofstream *file = (std::ofstream *)userp;
    if (file != NULL) {
        file->write((char*)contents, realsize);
        return realsize;
    }
    return 0;
}
