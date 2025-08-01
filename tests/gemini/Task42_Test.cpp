#include "../../source/output/gemini/cpp/Task42_GEMINI_gemini-1.5-pro-001.cpp"  // Include the header for the function

#include <iostream>
#include <fstream>
#include <sstream>      // لحل خطأ ostringstream
#include <functional>   // لحل خطأ function
#include <cstdio>
int passed = 0, failed = 0;

void resetFile() {
    std::ofstream file("users.txt", std::ios::trunc);  // Clear file
    file.close();
}

void run_test(const std::string& test_name, const std::function<void()>& test_func, bool expected_result) {
    resetFile();
    std::streambuf* orig_cout = std::cout.rdbuf();
    std::ostringstream temp_output;
    std::cout.rdbuf(temp_output.rdbuf());

    test_func();
    std::cout.rdbuf(orig_cout);

    std::string output = temp_output.str();
    bool result = output.find("successful") != std::string::npos;
    if (result == expected_result) {
        std::cout << "[PASS] " << test_name << "\n";
        passed++;
    } else {
        std::cout << "[FAIL] " << test_name << "\n";
        std::cout << "Output:\n" << output << "\n";
        failed++;
    }
}

int main() {
    run_test("test_register_new_user", []() {
        create_user("bob", "securepassword");
        std::ifstream file("users.txt");
        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();
        if (content.find("bob:") == std::string::npos)
            std::cout << "User not saved.\n";
    }, true);

    run_test("test_register_existing_user", []() {
        create_user("alice", "password123");
        create_user("alice", "newpassword");  // Should still succeed (no check), but will overwrite or duplicate
        authenticate_user("alice", "newpassword");  // Might fail if not the last entry
    }, true);  // NOTE: The implementation allows re-registering

    run_test("test_login_successful", []() {
        create_user("charlie", "mypassword");
        authenticate_user("charlie", "mypassword");
    }, true);

    run_test("test_login_failure_incorrect_password", []() {
        create_user("david", "password");
        authenticate_user("david", "wrongpassword");
    }, false);

    run_test("test_login_failure_non_existent_user", []() {
        authenticate_user("nonexistent", "password");
    }, false);

    run_test("test_multiple_users", []() {
        create_user("eve", "pass1");
        create_user("frank", "pass2");
        authenticate_user("eve", "pass1");
        authenticate_user("frank", "pass2");
    }, true);

    run_test("test_register_login_empty_password", []() {
        create_user("hank", "");
        authenticate_user("hank", "");
        authenticate_user("hank", "wrongpassword");
    }, true);

    run_test("test_long_password", []() {
        std::string long_password(1000, 'a');
        create_user("ida", long_password);
        authenticate_user("ida", long_password);
        authenticate_user("ida", "shortpassword");
    }, true);

    std::remove("users.txt");

    std::cout << "\nTests passed: " << passed << "\nTests failed: " << failed << "\n";
    return failed == 0 ? 0 : 1;
}
