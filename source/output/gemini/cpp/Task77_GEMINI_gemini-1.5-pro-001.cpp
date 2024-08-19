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
    if (argc != 5) {
        std::cerr << "Usage: ftp_downloader <hostname> <username> <password> <remote_filename>" << std::endl;
        return 1;
    }

    std::string hostname = argv[1];
    std::string username = argv[2];
    std::string password = argv[3];
    std::string remote_filename = argv[4];
    std::string local_filename = remote_filename.substr(remote_filename.find_last_of('/') + 1);

    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, ("ftp://" + hostname + "/" + remote_filename).c_str());
        curl_easy_setopt(curl, CURLOPT_USERPWD, (username + ":" + password).c_str());
        curl_easy_setopt(curl, CURLOPT_FTP_USE_EPSV, 1);
        //"error: ‘CURLOPT_FTP_PASSIVE’ was not declared in this scope; did you mean ‘CURLOPT_TFTP_BLKSIZE’? . line is commented"
        // curl_easy_setopt(curl, CURLOPT_FTP_PASSIVE, 1);
        curl_easy_setopt(curl, CURLOPT_FTP_SKIP_PASV_IP, 1);

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
            } else {
                std::cout << "File '" << local_filename << "' downloaded successfully." << std::endl;
            }
        } else {
            fprintf(stderr, "Error opening local file\n");
        }

        curl_easy_cleanup(curl);
    }

    return 0;
}
