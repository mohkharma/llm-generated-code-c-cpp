#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <random>
#include <openssl/sha.h>

#include "../../../source/output/gpt4o/cpp/Task135_OPENAI_gpt-4o.cpp"
// Helper to check if string is hex
bool is_hex_string(const std::string& s) {
    for (char c : s) {
        if (!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f'))) return false;
    }
    return true;
}

int main() {
    int passed = 0;
    int failed = 0;

    CSRFProtection csrf;

    // Test 1: Generated token should have SHA256 hex length + sessionId appended
    {
        std::string sessionId = "session123";
        std::string token = csrf.generateToken(sessionId);
        // SHA256 hex length = 64 chars
        if (token.length() >= 64 + sessionId.length()) {
            std::string hash_part = token.substr(0, 64);
            std::string session_part = token.substr(64);
            if (is_hex_string(hash_part) && session_part == sessionId) {
                std::cout << "[PASS] Test 1: Token format valid\n";
                passed++;
            } else {
                std::cout << "[FAIL] Test 1: Token content invalid\n";
                failed++;
            }
        } else {
            std::cout << "[FAIL] Test 1: Token length too short\n";
            failed++;
        }
    }

    // Test 2: Validation returns true with correct token and sessionId
    {
        std::string sessionId = "abc";
        std::string token = csrf.generateToken(sessionId);
        bool valid = csrf.validateToken(token, sessionId);
        if (valid) {
            std::cout << "[PASS] Test 2: Token validation success\n";
            passed++;
        } else {
            std::cout << "[FAIL] Test 2: Token validation failed\n";
            failed++;
        }
    }

    // Test 3: Validation returns false if sessionId mismatched
    {
        std::string sessionId = "abc";
        std::string token = csrf.generateToken(sessionId);
        bool valid = csrf.validateToken(token, "wrongSession");
        if (!valid) {
            std::cout << "[PASS] Test 3: Token validation correctly failed on wrong session\n";
            passed++;
        } else {
            std::cout << "[FAIL] Test 3: Token validation incorrectly passed\n";
            failed++;
        }
    }

    std::cout << "-------------------------------\n";
    std::cout << "Tests passed: " << passed << "\n";
    std::cout << "Tests failed: " << failed << "\n";

    if (failed == 0) {
        std::cout << "ALL TESTS PASSED.\n";
        return 0;
    } else {
        std::cout << "SOME TESTS FAILED.\n";
        return 1;
    }
}
