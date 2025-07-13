#include "../../../source/output/claude/cpp/Task128_CLAUDE_claude-3-5-sonnet-20240620.cpp"

#include <iostream>
#include <sstream>
#include <string>
#include <set>

// Helper to check if number is within bounds
bool isWithinRange(int val, int minVal, int maxVal) {
    return val >= minVal && val <= maxVal;
}

// Helper to check token properties
bool isValidToken(const std::string& token, int expectedLength) {
    const std::string validChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    if (token.length() != expectedLength) return false;
    for (char c : token) {
        if (validChars.find(c) == std::string::npos)
            return false;
    }
    return true;
}

int main() {
    int passed = 0;
    int total = 4;

    std::cout << "=== Running C++ Tests for Random Generator ===\n";

    // Test 1: generateRandomNumber(1, 100) multiple times
    bool numberInRange = true;
    for (int i = 0; i < 100; ++i) {
        int num = generateRandomNumber(1, 100);
        if (!isWithinRange(num, 1, 100)) {
            numberInRange = false;
            break;
        }
    }
    if (numberInRange) {
        std::cout << "[PASS] Random number is within range 1–100.\n";
        ++passed;
    } else {
        std::cout << "[FAIL] Random number is out of range 1–100.\n";
    }

    // Test 2: generateRandomNumber returns different values
    std::set<int> samples;
    for (int i = 0; i < 100; ++i) {
        samples.insert(generateRandomNumber(1, 100));
    }
    if (samples.size() > 1) {
        std::cout << "[PASS] Random number function produces varied results.\n";
        ++passed;
    } else {
        std::cout << "[FAIL] Random number function seems to return the same value.\n";
    }

    // Test 3: generateRandomToken(10) returns 10-character alphanumeric string
    std::string token = generateRandomToken(10);
    if (isValidToken(token, 10)) {
        std::cout << "[PASS] Random token of length 10 is valid.\n";
        ++passed;
    } else {
        std::cout << "[FAIL] Random token of length 10 is invalid.\n";
    }

    // Test 4: generateRandomToken(10) returns different values
    bool tokensDiffer = false;
    std::string prev = generateRandomToken(10);
    for (int i = 0; i < 50; ++i) {
        std::string current = generateRandomToken(10);
        if (current != prev) {
            tokensDiffer = true;
            break;
        }
    }
    if (tokensDiffer) {
        std::cout << "[PASS] Random token function produces varied results.\n";
        ++passed;
    } else {
        std::cout << "[FAIL] Random token function seems to return the same value.\n";
    }

    std::cout << "------------------------\n";
    std::cout << "Passed " << passed << " out of " << total << " tests.\n";

    return passed == total ? 0 : 1;
}
