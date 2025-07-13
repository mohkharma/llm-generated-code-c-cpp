#include "../../../source/output/gemini/cpp/Task126_GEMINI_gemini-1.5-pro-001.cpp"
#include <sstream>
#include <iostream>
#include <string>

bool test_redirect(const std::string& input, const std::string& expected_output, const std::string& test_name) {
    std::stringstream in(input);
    std::stringstream out;

    redirect_page(in, out);
    std::string output = out.str();

    if (output.find(expected_output) != std::string::npos) {
        std::cout << "[PASS] " << test_name << std::endl;
        return true;
    } else {
        std::cout << "[FAIL] " << test_name << std::endl;
        std::cout << "Expected to find: \"" << expected_output << "\"" << std::endl;
        std::cout << "Actual output:\n" << output << std::endl;
        return false;
    }
}

int main() {
    int passed = 0;
    int total = 5;

    passed += test_redirect("A\n", "Redirecting to page A...", "Test uppercase A");
    passed += test_redirect("b\n", "Redirecting to page B...", "Test lowercase b");
    passed += test_redirect("c\n", "Redirecting to page C...", "Test lowercase c");
    passed += test_redirect("D\n", "Invalid choice", "Test invalid letter D");
    passed += test_redirect("xyz\n", "Invalid choice", "Test full word xyz");

    std::cout << "------------------------" << std::endl;
    std::cout << "Passed " << passed << " out of " << total << " tests." << std::endl;

    return 0;
}
