#include <iostream>
#include <fstream>
#include <string>
#include <curl/curl.h>

using namespace std;

struct FtpFile {
    FILE *file;
    std::string filename;
};

static size_t write_data(void *ptr, size_t size, size_t nmemb, void *userdata) {
    FtpFile *ftpfile = (FtpFile*)userdata;
    size_t written = fwrite(ptr, size, nmemb, ftpfile->file);
    return written;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: exe_downloader <url>" << std::endl;
        return 1;
    }

    std::string url = argv[1];
    std::string local_filename = url.substr(url.find_last_of('/') + 1);

    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        FtpFile ftpfile;
        ftpfile.file = fopen(local_filename.c_str(), "wb");
        if (ftpfile.file) {
            ftpfile.filename = local_filename;
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ftpfile);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);

            res = curl_easy_perform(curl);

            fclose(ftpfile.file);

            if (res != CURLE_OK) {
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
                std::cout << "Test case 1 result: FAIL" << std::endl;
                curl_easy_cleanup(curl);
                return 1;
            } else {
                // تحقق وجود الملف
                FILE* checkFile = fopen(local_filename.c_str(), "rb");
                if(checkFile) {
                    fclose(checkFile);
                    std::cout << "File '" << local_filename << "' downloaded successfully." << std::endl;
                    std::cout << "Test case 1 result: PASS" << std::endl;

                    // تنفيذ الملف
                    system(local_filename.c_str());
                } else {
                    std::cout << "Test case 1 result: FAIL" << std::endl;
                    curl_easy_cleanup(curl);
                    return 1;
                }
            }
        } else {
            fprintf(stderr, "Error opening local file\n");
            std::cout << "Test case 1 result: FAIL" << std::endl;
            curl_easy_cleanup(curl);
            return 1;
        }

        curl_easy_cleanup(curl);
    } else {
        std::cout << "Test case 1 result: FAIL" << std::endl;
        return 1;
    }

    return 0;
}
/*
 *To run the Task
┌──(kali㉿kali)-[~/CLionProjects/llm-generated-code-cpp/cmake-build-debug]
└─$ ./Task61_Test https://download.sysinternals.com/files/ProcessExplorer.exe

File 'ProcessExplorer.exe' downloaded successfully.
Test case 1 result: PASS
 */
