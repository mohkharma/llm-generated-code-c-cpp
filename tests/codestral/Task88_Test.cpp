#include <iostream>
#include <fstream>
#include <random>
#include <sstream>
#include <iomanip>
#include <string>

std::string generateRandomString(int length) {
    const std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, characters.size() - 1);

    std::stringstream ss;
    for (int i = 0; i < length; i++) {
        ss << characters[dis(gen)];
    }
    return ss.str();
}

std::string stringToUnicode(const std::string& input) {
    std::stringstream ss;
    for (char c : input) {
        ss << "\\u" << std::setfill('0') << std::setw(4) << std::hex << static_cast<int>(c);
    }
    return ss.str();
}

bool test_temp_file(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) return false;
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    if (content.empty()) return false;
    return content.find("\\u") != std::string::npos;
}

int main() {
    std::ofstream tempFile("temp.txt", std::ios::out | std::ios::binary);

    std::string randomString = generateRandomString(10);
    std::string unicodeString = stringToUnicode(randomString);

    tempFile << unicodeString;
    tempFile.close();

    std::cout << "temp.txt" << std::endl;

    if (test_temp_file("temp.txt")) {
        std::cout << "Test case 1 result: PASS" << std::endl;
    } else {
        std::cout << "Test case 1 result: FAIL" << std::endl;
    }

    return 0;
}
