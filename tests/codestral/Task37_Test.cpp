#include "../../source/output/codestral/cpp/Task37_MISTRAL_codestral-latest.cpp"

#include <iostream>
#include <sstream>
#include <string>
#include <streambuf>
#include <cstdint>

std::string capture_output(const std::string& simulated_input) {
    std::istringstream input(simulated_input);
    std::cin.rdbuf(input.rdbuf());

    std::ostringstream output;
    std::streambuf* old_out = std::cout.rdbuf(output.rdbuf());

    queryUserByUsername();

    std::cout.rdbuf(old_out);
    std::cin.rdbuf(std::cin.rdbuf());

    return output.str();
}

int main() {
    int passed = 0;
    int failed = 0;

    std::cout << "Running test: test_existing_user" << std::endl;
    std::string output1 = capture_output("ahmad\n");
    if (output1.find("User found") != std::string::npos) {
        std::cout << "[PASS] test_existing_user" << std::endl;
        passed++;
    } else {
        std::cout << "[FAIL] test_existing_user\nOutput was:\n" << output1 << std::endl;
        failed++;
    }

    std::cout << "Running test: test_non_existing_user" << std::endl;
    std::string output2 = capture_output("nonexistent_user_xyz\n");
    if (output2.find("User not found") != std::string::npos) {
        std::cout << "[PASS] test_non_existing_user" << std::endl;
        passed++;
    } else {
        std::cout << "[FAIL] test_non_existing_user\nOutput was:\n" << output2 << std::endl;
        failed++;
    }

    std::cout << "===============================" << std::endl;
    std::cout << "Total Passed: " << passed << std::endl;
    std::cout << "Total Failed: " << failed << std::endl;

    return failed == 0 ? 0 : 1;
}
