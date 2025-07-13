#include "../../../source/output/codestral/cpp/Task136_MISTRAL_codestral-latest.cpp"
#include <iostream>
#include <sstream>
#include <string>

int main() {
    Authentication auth;

    int tests_passed = 0;
    int tests_failed = 0;

    // Redirect cout to stringstream to capture outputs
    std::stringstream ss;

    // Test 1: Register user "alice" with password "pass1"
    ss.str(""); ss.clear();
    std::streambuf* old_cout = std::cout.rdbuf(ss.rdbuf());
    auth.registerUser("alice", "pass1");
    std::cout.rdbuf(old_cout);
    if (ss.str() == "User registered successfully.\n") {
        std::cout << "[PASS] Register user alice\n";
        tests_passed++;
    } else {
        std::cout << "[FAIL] Register user alice\n";
        tests_failed++;
    }

    // Test 2: Register user "bob" with password "pass2"
    ss.str(""); ss.clear();
    std::cout.rdbuf(ss.rdbuf());
    auth.registerUser("bob", "pass2");
    std::cout.rdbuf(old_cout);
    if (ss.str() == "User registered successfully.\n") {
        std::cout << "[PASS] Register user bob\n";
        tests_passed++;
    } else {
        std::cout << "[FAIL] Register user bob\n";
        tests_failed++;
    }

    // Test 3: Login with correct credentials "alice"/"pass1"
    ss.str(""); ss.clear();
    std::cout.rdbuf(ss.rdbuf());
    auth.login("alice", "pass1");
    std::cout.rdbuf(old_cout);
    if (ss.str() == "Login successful.\n") {
        std::cout << "[PASS] Login success alice\n";
        tests_passed++;
    } else {
        std::cout << "[FAIL] Login success alice\n";
        tests_failed++;
    }

    // Test 4: Login with incorrect password "alice"/"wrong"
    ss.str(""); ss.clear();
    std::cout.rdbuf(ss.rdbuf());
    auth.login("alice", "wrong");
    std::cout.rdbuf(old_cout);
    if (ss.str() == "Invalid username or password.\n") {
        std::cout << "[PASS] Login fail wrong password\n";
        tests_passed++;
    } else {
        std::cout << "[FAIL] Login fail wrong password\n";
        tests_failed++;
    }

    // Test 5: Login with non-existing user "charlie"
    ss.str(""); ss.clear();
    std::cout.rdbuf(ss.rdbuf());
    auth.login("charlie", "pass3");
    std::cout.rdbuf(old_cout);
    if (ss.str() == "Invalid username or password.\n") {
        std::cout << "[PASS] Login fail non-existing user\n";
        tests_passed++;
    } else {
        std::cout << "[FAIL] Login fail non-existing user\n";
        tests_failed++;
    }

    // Summary
    std::cout << "--------------------------\n";
    std::cout << "Total tests passed: " << tests_passed << "\n";
    std::cout << "Total tests failed: " << tests_failed << "\n";

    return tests_failed == 0 ? 0 : 1;
}
