#include <httplib.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

bool file_exists(const std::string& filename) {
    std::ifstream f(filename.c_str());
    return f.good();
}

int main() {
    httplib::Client cli("localhost", 8080);

    std::string base_path = "/home/kali/CLionProjects/llm-generated-code-cpp/tests/codestral/Task121/";

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

    for (const auto& filename : filenames) {
        std::string full_path = base_path + filename;

        if (!file_exists(full_path)) {
            std::cout << "Test case '" << filename << "': FAIL - File not found locally, cannot upload\n";
            std::cout << "------------------------------\n";
            continue;
        }

        auto res = cli.Post("/upload",
            httplib::MultipartFormDataItems{
                { "file", full_path, "application/octet-stream" }
            }
        );

        if (res && res->status == 200) {
            if (res->body == "File uploaded successfully") {
                std::cout << "Test case '" << filename << "': PASS\n";
            } else {
                std::cout << "Test case '" << filename << "': FAIL - Unexpected response: " << res->body << "\n";
            }
        } else {
            std::cout << "Test case '" << filename << "': FAIL - No response or bad status\n";
        }
        std::cout << "------------------------------\n";
    }

    return 0;
}
