#include "../../source/output/codestral/cpp/Task42_MISTRAL_codestral-latest.cpp"  // Include the header for the function

#include <iostream>
#include <sstream>

int passed = 0, failed = 0;

void resetUsers() {
    users.clear();
    users["user1"] = "password1";
    users["user2"] = "password2";
}

void run_test(const std::string& test_name, const std::string& input, const std::string& expected_output) {
    resetUsers();

    std::streambuf* original_cin = std::cin.rdbuf();
    std::streambuf* original_cout = std::cout.rdbuf();

    std::stringstream fake_input(input);
    std::stringstream fake_output;

    std::cin.rdbuf(fake_input.rdbuf());
    std::cout.rdbuf(fake_output.rdbuf());

    authenticateUser();

    std::cin.rdbuf(original_cin);
    std::cout.rdbuf(original_cout);

    std::string output = fake_output.str();
    bool passed_test = output.find(expected_output) != std::string::npos;

    if (passed_test) {
        std::cout << "[PASS] " << test_name << "\n";
        passed++;
    } else {
        std::cout << "[FAIL] " << test_name << "\n";
        std::cout << "Expected to find: \"" << expected_output << "\"\n";
        std::cout << "Actual output: \"" << output << "\"\n";
        failed++;
    }
}

int main() {
    run_test("test_correct_credentials_user1", "user1\npassword1\n", "Authentication successful.");
    run_test("test_correct_credentials_user2", "user2\npassword2\n", "Authentication successful.");
    run_test("test_wrong_password", "user1\nwrongpass\n", "Invalid username or password.");
    run_test("test_nonexistent_user", "unknown\nwhatever\n", "Invalid username or password.");
    run_test("test_empty_username", "\npassword1\n", "Invalid username or password.");
    run_test("test_empty_password", "user1\n\n", "Invalid username or password.");
    run_test("test_case_sensitivity", "User1\npassword1\n", "Invalid username or password.");

    std::cout << "\nTests passed: " << passed << "\nTests failed: " << failed << "\n";
    return failed == 0 ? 0 : 1;
}
