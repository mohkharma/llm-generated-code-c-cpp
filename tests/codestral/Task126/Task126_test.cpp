#include "../../../source/output/codestral/cpp/Task126_MISTRAL_codestral-latest.cpp"
#include <sstream>
#include <iostream>
#include <string>

bool test_redirect(const std::string& input, const std::string& expected_output_part, const std::string& test_name) {
    std::stringstream in(input);
    std::stringstream out;

    handle_redirect(in, out);
    std::string output = out.str();

    if (output.find(expected_output_part) != std::string::npos) {
        std::cout << "[PASS] " << test_name << std::endl;
        return true;
    } else {
        std::cout << "[FAIL] " << test_name << std::endl;
        std::cout << "Expected to find: \"" << expected_output_part << "\"" << std::endl;
        std::cout << "Actual output:\n" << output << std::endl;
        return false;
    }
}

int main() {
    int passed = 0;
    int total = 4;

    passed += test_redirect("home\n", "Redirecting to home page...", "Test Home");
    passed += test_redirect("about\n", "Redirecting to about page...", "Test About");
    passed += test_redirect("contact\n", "Redirecting to contact page...", "Test Contact");
    passed += test_redirect("xyz\n", "Invalid input. Redirecting to default page...", "Test Invalid Input");

    std::cout << "------------------------" << std::endl;
    std::cout << "Passed " << passed << " out of " << total << " tests." << std::endl;

    return 0;
}
