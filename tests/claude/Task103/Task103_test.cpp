
#include <iostream>
#include <string>
#include <regex>

// #include "../../../source/output/claude/cpp/Task103_CLAUDE_claude-3-5-sonnet-20240620.cpp"
#include "../../../source/output/codestral/cpp/Task103_MISTRAL_codestral-latest.cpp"



#include <iostream>
#include <cassert>

// Test functions
void test_short_password() {
    assert(!checkPasswordStrength("Ab1"));
}

void test_no_uppercase() {
    assert(!checkPasswordStrength("abcdefgh1"));
}

void test_no_lowercase() {
    assert(!checkPasswordStrength("ABCDEF1"));
}

void test_no_digit() {
    assert(!checkPasswordStrength("Abcdefgh"));
}

void test_valid_password() {
    assert(checkPasswordStrength("Abcdefg1"));
}

void test_password_exactly_8_chars() {
    assert(checkPasswordStrength("A1bcdefg"));
}

void test_password_with_special_characters() {
    assert(checkPasswordStrength("A1@bcdEf"));
}

void test_all_uppercase() {
    assert(!checkPasswordStrength("ABCDEFGHI"));
}

void test_all_lowercase() {
    assert(!checkPasswordStrength("abcdefgh"));
}

void test_password_with_spaces() {
    assert(checkPasswordStrength("A1 bcdEf"));
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