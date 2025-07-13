#include "../../../source/output/llama-3/cpp/Task128_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"

#include <iostream>
#include <string>
#include <set>
#include <ctime>
#include <cstdlib>

bool isValidToken(const std::string& token, int length) {
    const std::string validChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    if (token.length() != length) return false;
    for (char c : token) {
        if (validChars.find(c) == std::string::npos)
            return false;
    }
    return true;
}

int main() {
    std::cout << "=== Running Tests for generateToken() ===\n";

    int passed = 0, total = 3;
    std::srand(std::time(0));

    // Test 1: Correct length
    std::string token = generateToken(12);
    if (token.length() == 12) {
        std::cout << "[PASS] Token has correct length (12).\n";
        ++passed;
    } else {
        std::cout << "[FAIL] Token has incorrect length: " << token.length() << "\n";
    }

    // Test 2: Only valid characters
    if (isValidToken(token, 12)) {
        std::cout << "[PASS] Token contains only valid characters.\n";
        ++passed;
    } else {
        std::cout << "[FAIL] Token contains invalid characters: " << token << "\n";
    }

    // Test 3: Tokens vary across calls
    std::set<std::string> samples;
    for (int i = 0; i < 20; ++i) {
        samples.insert(generateToken(12));
    }
    if (samples.size() > 1) {
        std::cout << "[PASS] Tokens vary across calls.\n";
        ++passed;
    } else {
        std::cout << "[FAIL] Tokens did not vary across calls.\n";
    }

    std::cout << "------------------------\n";
    std::cout << "Passed " << passed << " out of " << total << " tests.\n";

    return passed == total ? 0 : 1;
}
