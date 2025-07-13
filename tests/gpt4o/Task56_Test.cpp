#include "../../source/output/gpt4o/cpp/Task56_OPENAI_gpt-4o.cpp"
#include <iostream>
#include <sstream>
#include <string>
#include <cctype>

int tests_run = 0;
int tests_passed = 0;

#define ASSERT_TRUE(condition) \
do { \
++tests_run; \
if (condition) { \
std::cout << "[PASS] " << __func__ << "\n"; \
++tests_passed; \
} else { \
std::cout << "[FAIL] " << __func__ << "\n"; \
} \
} while(0)

// اعتراض الإخراج من stdout
std::string capture_output_of_generateToken() {
    std::streambuf* old_buf = std::cout.rdbuf();
    std::ostringstream temp_stream;
    std::cout.rdbuf(temp_stream.rdbuf());

    generateToken();  // من الحل

    std::cout.rdbuf(old_buf);
    return temp_stream.str();
}

bool isHex(const std::string& s) {
    for (char c : s) {
        if (!std::isxdigit(static_cast<unsigned char>(c))) return false;
    }
    return true;
}

void test_generated_token_is_32_hex_chars() {
    std::string output = capture_output_of_generateToken();

    std::string prefix = "C++ Generated Token: ";
    size_t pos = output.find(prefix);
    ASSERT_TRUE(pos != std::string::npos);

    std::string token = output.substr(pos + prefix.length(), 32);
    ASSERT_TRUE(token.length() == 32);
    ASSERT_TRUE(isHex(token));
}

void test_token_prints_newline() {
    std::string output = capture_output_of_generateToken();
    ASSERT_TRUE(output.back() == '\n' || output.back() == '\r');
}

int main() {
    test_generated_token_is_32_hex_chars();
    test_token_prints_newline();

    std::cout << "\nTotal tests run: " << tests_run << "\n";
    std::cout << "Total tests passed: " << tests_passed << "\n";
    std::cout << "Total tests failed: " << (tests_run - tests_passed) << "\n";

    return 0;
}
