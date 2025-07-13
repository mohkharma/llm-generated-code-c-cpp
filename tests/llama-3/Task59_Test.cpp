#include "../../source/output/llama-3/cpp/Task59_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"

#include <iostream>
#include <string>

#define ASSERT_TRUE(cond) \
if (cond) { ++passed; std::cout << "[PASS] "; } \
else { ++failed; std::cout << "[FAIL] "; }

int main() {
    int passed = 0, failed = 0;

    // test_all_unique_characters
    ASSERT_TRUE(accum("abcd") == "A-Bb-Ccc-Dddd");
    std::cout << "test_all_unique_characters\n";

    // test_mixed_case_characters
    ASSERT_TRUE(accum("RqaEzty") == "R-Qq-Aaa-Eeee-Zzzzz-Tttttt-Yyyyyyy");
    std::cout << "test_mixed_case_characters\n";

    // test_mixed_case_characters_with_repeating
    ASSERT_TRUE(accum("cwAt") == "C-Ww-Aaa-Tttt");
    std::cout << "test_mixed_case_characters_with_repeating\n";

    // test_single_character_string
    ASSERT_TRUE(accum("a") == "A");
    std::cout << "test_single_character_string\n";

    // test_all_uppercase_characters
    ASSERT_TRUE(accum("XYZ") == "X-Yy-Zzz");
    std::cout << "test_all_uppercase_characters\n";

    // test_all_lowercase_characters
    ASSERT_TRUE(accum("xyz") == "X-Yy-Zzz");
    std::cout << "test_all_lowercase_characters\n";

    // test_mixed_case_with_repeating_characters
    ASSERT_TRUE(accum("aAaA") == "A-Aa-Aaa-Aaaa");
    std::cout << "test_mixed_case_with_repeating_characters\n";

    // test_empty_string
    ASSERT_TRUE(accum("") == "");
    std::cout << "test_empty_string\n";

    // test_string_with_repeated_characters
    ASSERT_TRUE(accum("aaabbb") == "A-Aa-Aaa-Bbbb-Bbbbb-Bbbbbb");
    std::cout << "test_string_with_repeated_characters\n";

    // test_case_sensitivity_check
    ASSERT_TRUE(accum("AaBbCc") == "A-Aa-Bbb-Bbbb-Ccccc-Cccccc");
    std::cout << "test_case_sensitivity_check\n";

    std::cout << "\nTotal Passed: " << passed << "\n";
    std::cout << "Total Failed: " << failed << "\n";

    return failed == 0 ? 0 : 1;
}
