#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <filesystem>
#include <codecvt>
#include <locale>

namespace fs = std::filesystem;

std::string create_temp_file_with_unicode() {
    // Create a temporary file
    fs::path temp_path = fs::temp_directory_path() / fs::path("temp_file.txt");
    std::ofstream temp_file(temp_path, std::ios::out | std::ios::binary);

    // Generate a random string
    const std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, chars.size() - 1);
    std::string random_string;
    for (int i = 0; i < 10; ++i) {
        random_string += chars[dis(gen)];
    }

    // Convert the string to Unicode escape sequences
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring wide_string = converter.from_bytes(random_string);
    std::string unicode_string;
    for (wchar_t c : wide_string) {
        char buf[7];
        snprintf(buf, sizeof(buf), "\\\\u%04X", c);
        unicode_string += buf;
    }

    // Write the Unicode string to the file
    temp_file << unicode_string;
    temp_file.close();

    return temp_path.string();
}

// دالة للتحقق من التيست كيس
#include <fstream>

bool test_temp_file(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) return false;

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    if (content.empty()) return false;

    // تحقق من وجود escape sequence \u (مع تكرار أو على الأقل مرة واحدة)
    size_t found = content.find("\\u");
    return (found != std::string::npos);
}

int main() {
    std::string temp_file_path = create_temp_file_with_unicode();
    std::cout << temp_file_path << std::endl;

    if (test_temp_file(temp_file_path)) {
        std::cout << "Test case 1 result: PASS" << std::endl;
    } else {
        std::cout << "Test case 1 result: FAIL" << std::endl;
    }

    return 0;
}
