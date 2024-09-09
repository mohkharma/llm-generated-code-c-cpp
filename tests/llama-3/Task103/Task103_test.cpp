
#include <iostream>
#include <string>
#include <regex>

// #include "../../../source/output/claude/cpp/Task103_CLAUDE_claude-3-5-sonnet-20240620.cpp"
// #include "../../../source/output/codestral/cpp/Task103_MISTRAL_codestral-latest.cpp"
// #include "../../../source/output/gemini/cpp/Task103_GEMINI_gemini-1.5-pro-001.cpp"
// #include "../../../source/output/gpt4o/cpp/Task103_OPENAI_gpt-4o.cpp"
#include "../../../source/output/llama-3/cpp/Task103_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"



#include <iostream>
#include <cassert>

// Test functions
void test_short_password() {
    assert(!passwordStrength("Ab1"));
}

void test_no_uppercase() {
    assert(!passwordStrength("abcdefgh1"));
}

void test_no_lowercase() {
    assert(!passwordStrength("ABCDEF1"));
}

void test_no_digit() {
    assert(!passwordStrength("Abcdefgh"));
}

void test_valid_password() {
    assert(passwordStrength("Abcdefg1"));
}

void test_password_exactly_8_chars() {
    assert(passwordStrength("A1bcdefg"));
}

void test_password_with_special_characters() {
    assert(passwordStrength("A1@bcdEf"));
}

void test_all_uppercase() {
    assert(!passwordStrength("ABCDEFGHI"));
}

void test_all_lowercase() {
    assert(!passwordStrength("abcdefgh"));
}

void test_password_with_spaces() {
    assert(passwordStrength("A1 bcdEf"));
}

int main() {
    // Run all the test cases
    test_short_password();
    test_no_uppercase();
    test_no_lowercase();
    test_no_digit();
    test_valid_password();
    test_password_exactly_8_chars();
    test_password_with_special_characters();
    test_all_uppercase();
    test_all_lowercase();
    test_password_with_spaces();

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}