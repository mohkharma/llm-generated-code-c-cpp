#include <iostream>
#include <fstream>
#include <sstream>
#include "httplib.h"
#include <vector>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

// قراءة الملف إلى string
std::string readFileToString(const std::string& path) {
    std::ifstream ifs(path, std::ios::binary);
    std::ostringstream oss;
    oss << ifs.rdbuf();
    return oss.str();
}

std::string uploadFileViaHttp(const std::string& filename) {
    httplib::Client cli("localhost", 8080);

    std::string filepath = "testFiles/" + filename;
    if (!fs::exists(filepath)) {
        return "No file uploaded";
    }

    std::string fileContent = readFileToString(filepath);
    std::string boundary = "----MyCustomBoundary";

    std::string body;
    body += "--" + boundary + "\r\n";
    body += "Content-Disposition: form-data; name=\"file\"; filename=\"" + filename + "\"\r\n";
    body += "Content-Type: application/octet-stream\r\n\r\n";
    body += fileContent;
    body += "\r\n--" + boundary + "--\r\n";

    httplib::Headers headers = {
        { "Content-Type", "multipart/form-data; boundary=" + boundary }
    };

    auto res = cli.Post("/upload", headers, body, "multipart/form-data; boundary=" + boundary);
    if (res && res->status == 200) {
        return res->body;
    } else {
        return "Request failed";
    }
}

int main() {
    std::vector<std::string> filenames = {
        "test_file_1.txt",
        "large_file.txt",
        "file_with_!@#$%^&*()_+[]{};,.txt",
        "file_no_extension",
        "empty_file.txt",
        "non_existent_file.txt",
        "file with spaces.txt",
        "a_very_long_filename_that_exceeds_normal_length_limits_for_filenames.txt",
        "image_file.png",
        "file_with_newlines.txt",
        "file_not_found.txt"
    };

    int passed = 0;
    int total = filenames.size();

    for (const std::string& filename : filenames) {
        std::string result = uploadFileViaHttp(filename);

        std::string expected;
        std::string path = "testFiles/" + filename;
        if (fs::exists(path)) {
            expected = "File uploaded successfully";
        } else {
            expected = "No file uploaded";
        }

        if (result == expected) {
            std::cout << "[✅] Passed: " << filename << "\n";
            passed++;
        } else {
            std::cout << "[❌] Failed: " << filename << "\n";
            std::cout << "Expected: " << expected << "\n";
            std::cout << "Got:      " << result << "\n";
        }

        std::cout << "------------------------\n";
    }

    std::cout << "Summary: " << passed << "/" << total << " tests passed.\n";
    return 0;
}
