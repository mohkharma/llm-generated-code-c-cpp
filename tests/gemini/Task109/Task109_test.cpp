#include <iostream>
#include <regex>
#include <string>
#include <cassert>
#include <sstream>

#include "../../../source/output/gemini/cpp/Task109_GEMINI_gemini-1.5-pro-001.cpp"  // Include the header for the function


int main() {
    // Direct test cases with assert
    assert(foo("test@example.com") == true); // Valid email
    assert(foo("test.email@example.com") == true); // Valid email
    assert(foo("test.email+alex@leetcode.com") == true); // Valid email
    assert(foo("test.email@com") == false); // Invalid email, missing domain
    assert(foo("test.email@.com") == false); // Invalid email, missing username
    assert(foo("test@.com") == false); // Invalid email, missing domain
    assert(foo("test@com") == false); // Invalid email, missing domain part
    assert(foo("test@com.") == false); // Invalid email, invalid domain part
    assert(foo("test@com.c") == false); // Invalid email, domain part too short
    assert(foo("") == false); // Invalid email, empty

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}