#include "../../../source/output/claude/cpp/Task126_CLAUDE_claude-3-5-sonnet-20240620.cpp"
#include <sstream>
#include <string>
#include <iostream>

bool test_redirect(const std::string& input, const std::string& expected_url, const std::string& test_name) {
    std::stringstream in(input);
    std::stringstream out;

    redirect_user(in, out);
    std::string output = out.str();

    if (output.find(expected_url) != std::string::npos) {
        std::cout << "[PASS] " << test_name << std::endl;
        return true;
    } else {
        std::cout << "[FAIL] " << test_name << std::endl;
        std::cout << "Expected to find: \"" << expected_url << "\"" << std::endl;
        std::cout << "Actual output:\n" << output << std::endl;
        return false;
    }
}

int main() {
    int passed = 0;
    int total = 4;

    passed += test_redirect("1\n", "https://www.google.com", "Test Google");
    passed += test_redirect("2\n", "https://www.youtube.com", "Test YouTube");
    passed += test_redirect("3\n", "https://www.wikipedia.org", "Test Wikipedia");
    passed += test_redirect("5\n", "Invalid choice", "Test Invalid Input");

    std::cout << "------------------------" << std::endl;
    std::cout << "Passed " << passed << " out of " << total << " tests." << std::endl;

    return 0;
}
