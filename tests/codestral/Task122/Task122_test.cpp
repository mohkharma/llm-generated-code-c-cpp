#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <cassert>

#include "../../../source/output/codestral/cpp/Task122_MISTRAL_codestral-latest.cpp"

void clear_state() {
    passwords.clear();
}

void assert_stored(const std::string& username, const std::string& expected_password) {
    auto it = passwords.find(username);
    assert(it != passwords.end() && "Username not found");
    assert(it->second == expected_password && "Stored password does not match expected");
}

void test_case(const std::string& case_name, const std::string& username, const std::string& password) {
    std::cout << case_name << std::endl;
    signup(username, password);
    assert_stored(username, password);
}

int main() {
    clear_state();

    try {
        test_case("Test Case 1: Normal Signup", "user1", "password123");
        test_case("Test Case 2: Special Characters Username", "user!@#", "password123");
        test_case("Test Case 3: Special Characters Password", "user2", "pass!@#123");
        test_case("Test Case 4: Empty Username", "", "password123");
        test_case("Test Case 5: Empty Password", "user3", "");
        test_case("Test Case 6: Long Username and Password", std::string(100, 'u'), std::string(100, 'p'));
        test_case("Test Case 7: Multiple Users A", "user4", "password1");
        test_case("Test Case 7: Multiple Users B", "user5", "password2");
        test_case("Test Case 8: Identical Usernames", "user6", "password3");
        test_case("Test Case 8: Identical Usernames Overwrite", "user6", "password4");
        test_case("Test Case 9: Simple Add", "user7", "password5");
        test_case("Test Case 10: Null Characters", "user\0", "pass\0word"); // Only "user" will be used
        test_case("Test Case 11: Duplicate Entries", "user8", "password6");
        test_case("Test Case 11: Duplicate Entries Again", "user8", "password6");
        test_case("Test Case 12: Very Long Data", std::string(1000, 'u'), std::string(1000, 'p'));
        for (int i = 0; i < 10; ++i) {
            test_case("Test Case 13: File Size Simulated Entry " + std::to_string(i), "user" + std::to_string(i), "password123");
        }
        test_case("Test Case 17: Multiple Extensions", "user.with.many.extensions", "password");
        test_case("Test Case 18: Security (No Plaintext Check)", "user11", "password11");
        test_case("Test Case 19: Exception Simulation", "user12", "password12");

        std::cout << "\n✅ All Gemini-style tests passed successfully.\n";
    } catch (const std::exception& e) {
        std::cerr << "❌ Test failed with exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "❌ Test failed with unknown error.\n";
        return 1;
    }

    return 0;
}
