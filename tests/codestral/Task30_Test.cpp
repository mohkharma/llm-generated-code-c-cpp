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

//#include "../../source/output/claude/cpp/Task30_CLAUDE_claude-3-5-sonnet-20240620.cpp"  // Include the header for the function
 #include "../../source/output/codestral/cpp/Task30_MISTRAL_codestral-latest.cpp"  // Include the header for the function
// #include "../../source/output/gemini/cpp/Task30_GEMINI_gemini-1.5-pro-001.cpp"  // Include the header for the function
// #include "../../source/output/gpt4o/cpp/Task30_OPENAI_gpt-4o.cpp"  // Include the header for the function
// #include "../../source/output/llama-3/cpp/Task30_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"  // Include the header for the function


void testLongest() {
    // Test with distinct characters in s1 and s2
    assert(longest("xyaabbbccccdefww", "xxxxyyyyabklmopq") == "abcdefklmopqwxy");

    // Test with identical strings
    assert(longest("abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxyz") == "abcdefghijklmnopqrstuvwxyz");

    // Test with both strings empty
    assert(longest("", "") == "");

    // Test with one string empty and the other full
    assert(longest("", "abcdef") == "abcdef");

    // Test with no overlapping characters between s1 and s2
    assert(longest("abc", "def") == "abcdef");

    // Test with all characters in s1 and s2 overlapping
    assert(longest("abc", "abcd") == "abcd");

    // Test with case sensitivity (input should only include lowercase letters)
    assert(longest("abc", "xyzf") == "abcfxyz");

    // Test with long strings
    assert(longest("abcdefghijklmnopqrstuvwxyzaaa", "zyxwvutsrqponmlkjihgfedcbaaaa") == "abcdefghijklmnopqrstuvwxyz");

    // Test with single character strings
    assert(longest("a", "a") == "a");

    // Test with repeated characters
    assert(longest("aaaa", "bbbbccccdddd") == "abcd");
}

int main() {
    testLongest();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}