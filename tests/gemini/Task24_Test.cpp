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

// #include "../../source/output/claude/cpp/Task24_CLAUDE_claude-3-5-sonnet-20240620.cpp"  // Include the header for the function
// #include "../../source/output/codestral/cpp/Task24_MISTRAL_codestral-latest.cpp"  // Include the header for the function
#include "../../source/output/gemini/cpp/Task24_GEMINI_gemini-1.5-pro-001.cpp"  // Include the header for the function
// #include "../../source/output/gpt4o/cpp/Task24_OPENAI_gpt-4o.cpp"  // Include the header for the function
// #include "../../source/output/llama-3/cpp/Task24_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"  // Include the header for the function

void testValid4DigitPIN() {
    assert(validate_pin("1234") == true);
}

void testValid6DigitPIN() {
    assert(validate_pin("123456") == true);
}

void testInvalidLengthPINTooShort() {
    assert(validate_pin("123") == false);
}

void testInvalidLengthPINTooLong() {
    assert(validate_pin("1234567") == false);
}

void testInvalidPINWithLetters() {
    assert(validate_pin("a234") == false);
}

void testInvalidPINWithSpecialCharacters() {
    assert(validate_pin("12@4") == false);
}

void testValid6DigitPINWithLeadingZeros() {
    assert(validate_pin("000123") == true);
}

void testValid4DigitPINWithLeadingZeros() {
    assert(validate_pin("0001") == true);
}

void testInvalidPINWithSpaces() {
    assert(validate_pin("12 34") == false);
}

void testEmptyPIN() {
    assert(validate_pin("") == false);
}

int main() {
    testValid4DigitPIN();
    testValid6DigitPIN();
    testInvalidLengthPINTooShort();
    testInvalidLengthPINTooLong();
    testInvalidPINWithLetters();
    testInvalidPINWithSpecialCharacters();
    testValid6DigitPINWithLeadingZeros();
    testValid4DigitPINWithLeadingZeros();
    testInvalidPINWithSpaces();
    testEmptyPIN();

    printf("All test cases passed!\n");
    return 0;
}