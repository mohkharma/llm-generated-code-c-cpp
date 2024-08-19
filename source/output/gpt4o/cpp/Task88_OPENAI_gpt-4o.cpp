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

int main() {
    // Generate a random string
    std::string randomString = generate_random_string(10);

    // Convert string into Unicode
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring unicodeString = converter.from_bytes(randomString);

    //error: ‘unique_path’ is not a member of ‘std::filesystem’
    //fixed by regeneration of response
    // std::filesystem::path tempFile = std::filesystem::temp_directory_path() / std::filesystem::unique_path();
    // Create a unique temporary file path
    std::filesystem::path tempFile = std::filesystem::temp_directory_path() / (generate_random_string(10) + ".txt");

    // Write the Unicode string to the temporary file
    std::wofstream file(tempFile);
    file.imbue(std::locale(file.getloc(), new std::codecvt_utf8_utf16<wchar_t>));
    file << unicodeString;
    file.close();

    // Output the path of the temporary file
    std::wcout << L"Temporary file created: " << tempFile.wstring() << std::endl;

    return 0;
}
