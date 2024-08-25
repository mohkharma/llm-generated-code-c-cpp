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

//#include "../../source/output/claude/cpp/Task19_CLAUDE_claude-3-5-sonnet-20240620.cpp"  // Include the header for the function
// #include "../../source/output/codestral/cpp/Task19_MISTRAL_codestral-latest.cpp"  // Include the header for the function
 #include "../../source/output/gemini/cpp/Task19_GEMINI_gemini-1.5-pro-001.cpp"  // Include the header for the function
// #include "../../source/output/gpt4o/cpp/Task19_OPENAI_gpt-4o.cpp"  // Include the header for the function
// #include "../../source/output/llama-3/cpp/Task19_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"  // Include the header for the function


// Test Cases
void runTests() {
    // Test Case 1
    {
        std::string sentence = "Hey fellow warriors";
        std::string expected = "Hey wollef sroirraw";
        assert(spinWords(sentence) == expected);
    }

    // Test Case 2
    {
        std::string sentence = "This is a test";
        std::string expected = "This is a test";
        assert(spinWords(sentence) == expected);
    }

    // Test Case 3
    {
        std::string sentence = "This is another test";
        std::string expected = "This is rehtona test";
        assert(spinWords(sentence) == expected);
    }

    // Test Case 4
    {
        std::string sentence = "Welcome to the jungle";
        std::string expected = "emocleW to the elgnuj";
        assert(spinWords(sentence) == expected);
    }

    // Test Case 5
    {
        std::string sentence = "You are amazing";
        std::string expected = "You are gnizama";
        assert(spinWords(sentence) == expected);
    }

    // Test Case 6
    {
        std::string sentence = "Just a simple example";
        std::string expected = "Just a elpmis elpmaxe";
        assert(spinWords(sentence) == expected);
    }

    // Test Case 7
    {
        std::string sentence = "Short words are not reversed";
        std::string expected = "trohS sdrow are not desrever";
        assert(spinWords(sentence) == expected);
    }

    // Test Case 8
    {
        std::string sentence = "Reverse only long words";
        std::string expected = "esreveR only long sdrow";
        assert(spinWords(sentence) == expected);
    }

    // Test Case 9
    {
        std::string sentence = "Exceptional cases should work too";
        std::string expected = "lanoitpecxE sesac dluohs work too";
        assert(spinWords(sentence) == expected);
    }

    // Test Case 10
    {
        std::string sentence = "This sentence contains multiple long words";
        std::string expected = "This ecnetnes sniatnoc elpitlum long sdrow";
        assert(spinWords(sentence) == expected);
    }

    std::cout << "All test cases passed!" << std::endl;
}

int main() {
    runTests();
    return 0;
}