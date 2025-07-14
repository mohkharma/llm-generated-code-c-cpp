#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <locale>

std::string getRandomString() {
    std::string SALTCHARS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::string salt;
    srand(time(0));
    while (salt.length() < 10) {
        salt += SALTCHARS[rand() % SALTCHARS.length()];
    }
    return salt;
}

std::string toUnicode(const std::string& str) {
    std::string unicodeString;
    for (char c : str) {
        unicodeString += "\\u";
        unicodeString += std::to_string(static_cast<int>(c));
    }
    return unicodeString;
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
    std::string randomString = getRandomString();
    std::string unicodeString = toUnicode(randomString);
    std::string tempFileName = "temp_" + getRandomString() + ".txt";

    std::ofstream tempFile(tempFileName, std::ios::out | std::ios::binary);
    tempFile.imbue(std::locale("en_US.UTF-8"));
    tempFile << unicodeString;
    tempFile.close();

    std::cout << tempFileName << std::endl;

    if (test_temp_file(tempFileName)) {
        std::cout << "Test case 1 result: PASS" << std::endl;
    } else {
        std::cout << "Test case 1 result: FAIL" << std::endl;
    }

    return 0;
}
