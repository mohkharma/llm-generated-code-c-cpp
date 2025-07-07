#include <iostream>
#include <string>
#include <regex>
#include <cassert>


#include "../../../source/output/llama-3/cpp/Task109_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"


void runTests() {
    // Valid inputs
    assert(foo("valid123") == 1);
    assert(foo("123") == 1);
    assert(foo("valid") == 1);

    // Invalid inputs
    assert(foo("invalid input") == 0);
    // Contains a space
    assert(foo("!@#$%^&*()") == 0);
    // Contains special characters
    assert(foo("invalid!") == 0);
    // Contains an exclamation mark
    assert(foo("1234567890!") == 0);
    // Contains a special character
    assert(foo("") == 0);
    // Empty string

    assert(foo("anotherValid_input") == 1);
    assert(foo("input_with_underscore") == 1);

    std::cout << "All tests passed!" << std::endl;
}

int main() {
    runTests();
    return 0;
}