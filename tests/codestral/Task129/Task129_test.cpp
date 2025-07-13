#include "../../../source/output/codestral/cpp/Task129_MISTRAL_codestral-latest.cpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <curl/curl.h>
#include <cstdio>

// دالة تستعمل WriteCallback وتكمل ما ينقص من الحل
void retrieveFile(const std::string& filename) {
    std::string serverUrl = "http://127.0.0.1:8000/";  // عدّل هذا حسب مكان السيرفر
    std::string fileUrl = serverUrl + filename;

    CURL* curl;
    CURLcode res;
    std::ofstream outFile(filename, std::ios::binary);

    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to open file for writing." << std::endl;
        return;
    }

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, fileUrl.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &outFile);

        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        outFile.close();

        if (res == CURLE_OK) {
            std::cout << "File '" << filename << "' successfully retrieved and saved." << std::endl;
        } else {
            std::cerr << "Error retrieving file: " << curl_easy_strerror(res) << std::endl;
        }
    } else {
        std::cerr << "Error: Unable to initialize CURL." << std::endl;
        outFile.close();
    }
}

// دالة اختبار
void run_test(const std::string& test_name, const std::string& input_filename, const std::string& expected_substring, bool should_exist) {
    std::remove(input_filename.c_str());

    std::stringstream output;
    std::streambuf* original_cout = std::cout.rdbuf();
    std::streambuf* original_cerr = std::cerr.rdbuf();
    std::cout.rdbuf(output.rdbuf());
    std::cerr.rdbuf(output.rdbuf());

    retrieveFile(input_filename);

    std::cout.rdbuf(original_cout);
    std::cerr.rdbuf(original_cerr);

    std::string result = output.str();

    bool contains_message = result.find(expected_substring) != std::string::npos;

    bool file_saved = false;
    std::ifstream file(input_filename, std::ios::binary);
    if (file.is_open()) {
        file_saved = true;
        file.close();
        std::remove(input_filename.c_str());
    }

    bool pass = contains_message && (file_saved == should_exist);

    if (pass) {
        std::cout << "[PASS] " << test_name << std::endl;
    } else {
        std::cout << "[FAIL] " << test_name << std::endl;
        std::cout << "  ⮕ Output: " << result << std::endl;
        std::cout << "  ⮕ Expected: \"" << expected_substring << "\" | File saved? " << (file_saved ? "Yes" : "No") << std::endl;
    }
}

int main() {
    run_test("Retrieve existing file", "testFile.txt", "successfully", true);
    run_test("Retrieve missing file", "nonexistent.txt", "Error", false);
    return 0;
}
