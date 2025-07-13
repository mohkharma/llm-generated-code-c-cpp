#include "../../../source/output/claude/cpp/Task136_CLAUDE_claude-3-5-sonnet-20240620.cpp"
#include <iostream>
#include <sstream>
#include <string>

int main() {
    int tests_passed = 0;
    int tests_failed = 0;

    // Test 1: Register new user "alice" with password "password123"
    {
        std::stringstream input;
        std::stringstream output;

        // Simulate registration call (no direct I/O in solution, so call function directly)
        bool result = register_user("alice", "password123");

        if (result) {
            std::cout << "[PASS] Register new user 'alice'\n";
            tests_passed++;
        } else {
            std::cout << "[FAIL] Register new user 'alice'\n";
            tests_failed++;
        }
    }

    // Test 2: Register existing user "alice" again should fail
    {
        bool result = register_user("alice", "newpass");

        if (!result) {
            std::cout << "[PASS] Register existing user 'alice' rejected\n";
            tests_passed++;
        } else {
            std::cout << "[FAIL] Register existing user 'alice' accepted\n";
            tests_failed++;
        }
    }

    // Test 3: Login with correct credentials for "alice"
    {
        bool result = login("alice", "password123");

        if (result) {
            std::cout << "[PASS] Login with correct credentials for 'alice'\n";
            tests_passed++;
        } else {
            std::cout << "[FAIL] Login with correct credentials for 'alice'\n";
            tests_failed++;
        }
    }

    // Test 4: Login with incorrect password for "alice"
    {
        bool result = login("alice", "wrongpass");

        if (!result) {
            std::cout << "[PASS] Login fails with incorrect password for 'alice'\n";
            tests_passed++;
        } else {
            std::cout << "[FAIL] Login succeeds with incorrect password for 'alice'\n";
            tests_failed++;
        }
    }

    // Test 5: Login for non-existent user "bob"
    {
        bool result = login("bob", "anything");

        if (!result) {
            std::cout << "[PASS] Login fails for non-existent user 'bob'\n";
            tests_passed++;
        } else {
            std::cout << "[FAIL] Login succeeds for non-existent user 'bob'\n";
            tests_failed++;
        }
    }

    // Summary
    std::cout << "--------------------------\n";
    std::cout << "Total tests passed: " << tests_passed << "\n";
    std::cout << "Total tests failed: " << tests_failed << "\n";

    return (tests_failed == 0) ? 0 : 1;
}
