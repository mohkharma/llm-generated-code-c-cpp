#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>

// Generates a random 16-character session ID
std::string generateSessionID() {
    std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    std::string sessionID;
    for (int i = 0; i < 16; i++) {
        sessionID += characters[rand() % characters.length()];
    }
    return sessionID;
}

// Check if string contains only allowed characters
bool isValidSessionID(const std::string& id) {
    std::string allowed = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    for (char c : id) {
        if (allowed.find(c) == std::string::npos) return false;
    }
    return true;
}

void run_tests() {
    srand(time(nullptr));

    for (int i = 0; i < 5; i++) {
        std::string id = generateSessionID();
        bool length_ok = (id.length() == 16);
        bool chars_ok = isValidSessionID(id);
        std::cout << "Test " << i+1 << ": " << id
                  << " | Length: " << (length_ok ? "OK" : "FAIL")
                  << " | Valid chars: " << (chars_ok ? "OK" : "FAIL")
                  << std::endl;
    }
}

int main() {
    run_tests();
    return 0;
}
