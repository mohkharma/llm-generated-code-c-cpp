#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <filesystem>
#include <cctype>

std::string createTempFileWithUnicode() {
    try {
        // Create a temporary file path
        std::string tempFilePath = std::filesystem::temp_directory_path().string() + "/temp_" + std::to_string(rand()) + ".txt";
        std::ofstream tempFile(tempFilePath, std::ios::out | std::ios::binary);

        // Generate a random string
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<char> distribution('a', 'z');
        std::string randomString(10, ' ');
        for (char& c : randomString) {
            c = distribution(generator);
        }

        // Write the string to the file (UTF-8 text)
        tempFile << randomString;
        tempFile.close();

        return tempFilePath;

    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return "";
    }
}

bool test_temp_file(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) return false;

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    if (content.size() != 10) return false;
    for (char c : content) {
        if (c < 'a' || c > 'z') return false;
    }
    return true;
}

int main() {
    std::string tempFilePath = createTempFileWithUnicode();
    if (tempFilePath.empty()) {
        std::cout << "Test case 1 result: FAIL" << std::endl;
        return 1;
    }

    std::cout << "Temporary file created at: " << tempFilePath << std::endl;

    if (test_temp_file(tempFilePath)) {
        std::cout << "Test case 1 result: PASS" << std::endl;
    } else {
        std::cout << "Test case 1 result: FAIL" << std::endl;
    }

    return 0;
}
