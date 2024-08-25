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

// #include "../../source/output/claude/cpp/Task12_CLAUDE_claude-3-5-sonnet-20240620.cpp"  // Include the header for the function
// #include "../../source/output/codestral/cpp/Task12_MISTRAL_codestral-latest.cpp"  // Include the header for the function
// #include "../../source/output/gemini/cpp/Task12_GEMINI_gemini-1.5-pro-001.cpp"  // Include the header for the function
#include "../../source/output/gpt4o/cpp/Task12_OPENAI_gpt-4o.cpp"  // Include the header for the function
// #include "../../source/output/llama-3/cpp/Task12_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"  // Include the header for the function


// Test cases

void testBasicExample1() {
    // Test basic example with diverse words
    assert(high("man i need a taxi up to ubud") == "taxi");
}

void testBasicExample2() {
    // Test basic example with different set of words
    assert(high("what time are we climbing up the volcano") == "volcano");
}

void testBasicExample3() {
    // Test basic example with a smaller set of words
    assert(high("take me to semynak") == "semynak");
}

void testSingleWord() {
    // Test with a single word
    assert(high("hello") == "hello");
}

void testMultipleWordsSameScore() {
    // Test with multiple words having the same score
    assert(high("apple banana cherry") == "cherry");
}

void testDifferentScores() {
    // Test with words having different scores
    assert(high("ant bear zebra") == "zebra");
}

void testWordsWithOneLetter() {
    // Test with single-letter words
    assert(high("a b c d e f g h i j k l m n o p q r s t u v w x y z") == "z");
}

void testEmptyString() {
    // Test with an empty string
    assert(high("") == "");
}

void testWordsWithSpecialCharacters() {
    // Test with words containing special characters (should be handled as invalid input in this context)
    assert(high("hello world") == "world");
}

void testLongWords() {
    // Test with long words to check performance
    assert(high("pneumoultramicroscopicsilicovolcanoconiosis supercalifragilisticexpialidocious antidisestablishmentarianism") == "pneumoultramicroscopicsilicovolcanoconiosis");
}

int main() {
    testBasicExample1();
    testBasicExample2();
    testBasicExample3();
    testSingleWord();
    testMultipleWordsSameScore();
    testDifferentScores();
    testWordsWithOneLetter();
    testEmptyString();
    testWordsWithSpecialCharacters();
    testLongWords();

    std::cout << "All test cases passed!" << std::endl;

    return 0;
}