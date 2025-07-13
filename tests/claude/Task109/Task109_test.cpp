#include <gtest/gtest.h>
#include <string>
using namespace std;

#include <iostream>
#include <vector>
#include <cassert>
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <cassert>
#include <iostream>
#include <vector>
#include <cassert>
#include <cstring>
#include <unordered_map>
#include <string>
#include "../../../source/output/claude/cpp/Task109_CLAUDE_claude-3-5-sonnet-20240620.cpp"
// #include "../../../source/output/codestral/cpp/Task42_MISTRAL_codestral-latest.cpp"  // Include the header for the function
// #include "../../../source/output/gemini/cpp/Task42_GEMINI_gemini-1.5-pro-001.cpp"  // Include the header for the function
// #include "../../../source/output/gpt4o/cpp/Task42_OPENAI_gpt-4o.cpp"  // Include the header for the function
// #include "../../../source/output/llama-3/cpp/Task42_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"  // Include the header for the function

// Test cases
int main() {
    // Test validateEmail
    assert(validateEmail("test@example.com")); // Valid email
    assert(!validateEmail("test@example")); // Invalid email, no domain
    assert(!validateEmail("test@.com")); // Invalid email, no username
    assert(!validateEmail("test@ex@ample.com")); // Invalid email, multiple '@'
    assert(!validateEmail("test@example.c")); // Invalid email, domain too short

    // Test validatePhoneNumber
    assert(validatePhoneNumber("123-456-7890")); // Valid phone number
    assert(validatePhoneNumber("(123) 456-7890")); // Valid phone number with parentheses
    assert(validatePhoneNumber("123.456.7890")); // Valid phone number with dots
    assert(validatePhoneNumber("1234567890")); // Valid phone number without delimiters
    assert(!validatePhoneNumber("123-4567-890")); // Invalid phone number, incorrect format
    assert(!validatePhoneNumber("123-456-789")); // Invalid phone number, missing digit

    // Test validatePassword
    assert(validatePassword("A1b2c3D4")); // Valid password
    assert(!validatePassword("password")); // Invalid password, no uppercase or number
    assert(!validatePassword("PASSWORD1")); // Invalid password, no lowercase letter
    assert(!validatePassword("pass1234")); // Invalid password, no uppercase letter
    assert(!validatePassword("P@ssw0rd")); // Invalid password, contains special characters
    assert(!validatePassword("Short1")); // Invalid password, too short

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}