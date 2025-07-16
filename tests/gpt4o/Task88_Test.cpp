#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <filesystem>
#include <locale>
#include <codecvt>

std::string generate_random_string(size_t length) {
    std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    std::string randomString;
    std::default_random_engine rng(std::random_device{}());
    std::uniform_int_distribution<> dist(0, characters.size() - 1);
    for (size_t i = 0; i < length; ++i) {
        randomString += characters[dist(rng)];
    }
    return randomString;
}

bool test_temp_file(const std::filesystem::path& path) {
    std::wifstream file(path);
    if (!file.is_open()) return false;
    file.imbue(std::locale(file.getloc(), new std::codecvt_utf8_utf16<wchar_t>));
    std::wstring content((std::istreambuf_iterator<wchar_t>(file)), std::istreambuf_iterator<wchar_t>());
    file.close();
    return !content.empty();
}

int main() {
    std::string randomString = generate_random_string(10);

    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring unicodeString = converter.from_bytes(randomString);

    std::filesystem::path tempFile = std::filesystem::temp_directory_path() / (generate_random_string(10) , L".txt");

    std::wofstream file(tempFile);
    file.imbue(std::locale(file.getloc(), new std::codecvt_utf8_utf16<wchar_t>));
    file << unicodeString;
    file.close();

    std::wcout << L"Temporary file created: " << tempFile.wstring() << std::endl;

    if (test_temp_file(tempFile)) {
        std::wcout << L"Test case 1 result: PASS" << std::endl;
    } else {
        std::wcout << L"Test case 1 result: FAIL" << std::endl;
    }

    return 0;
}
