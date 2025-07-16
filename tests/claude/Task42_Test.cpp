#include "../../source/output/claude/cpp/Task42_CLAUDE_claude-3-5-sonnet-20240620.cpp"  // Include the header for the function

#include <iostream>
#include <sstream>

int passed = 0, failed = 0;

void print_result(const std::string& test_name, bool condition) {
    if (condition) {
        std::cout << "[PASS] " << test_name << "\n";
        passed++;
    } else {
        std::cout << "[FAIL] " << test_name << "\n";
        failed++;
    }
}

int main() {
    users.clear();

    // test_register_new_user
    users.clear();
    print_result("test_register_new_user", register_user("bob", "securepassword") && users.find("bob") != users.end());

    // test_register_existing_user
    users.clear();
    register_user("alice", "password123");
    print_result("test_register_existing_user", register_user("alice", "newpassword") == false);

    // test_login_successful
    users.clear();
    register_user("charlie", "mypassword");
    print_result("test_login_successful", login("charlie", "mypassword"));

    // test_login_failure_incorrect_password
    users.clear();
    register_user("david", "password");
    print_result("test_login_failure_incorrect_password", login("david", "wrongpassword") == false);

    // test_login_failure_non_existent_user
    users.clear();
    print_result("test_login_failure_non_existent_user", login("nonexistent", "password") == false);

    // test_multiple_users
    users.clear();
    register_user("eve", "pass1");
    register_user("frank", "pass2");
    print_result("test_multiple_users", login("eve", "pass1") && login("frank", "pass2"));

    // test_hash_consistency
    {
        std::string password = "password";
        std::vector<unsigned char> hash1 = hash_password(password, [](){
            std::vector<unsigned char> salt(32);
            RAND_bytes(salt.data(), salt.size());
            return salt;
        }());
        std::vector<unsigned char> hash2 = hash_password(password, [](){
            std::vector<unsigned char> salt(32);
            RAND_bytes(salt.data(), salt.size());
            return salt;
        }());
        bool hashes_different = (hash1 != hash2);
        bool verify_works = verify_password(hash1, password);
        print_result("test_hash_consistency", hashes_different && verify_works);
    }

    // test_login_with_altered_stored_password
    users.clear();
    register_user("grace", "password");
    users["grace"] = hash_password("differentpassword", [](){
        std::vector<unsigned char> salt(32);
        RAND_bytes(salt.data(), salt.size());
        return salt;
    }());
    print_result("test_login_with_altered_stored_password", login("grace", "password") == false);

    // test_register_login_empty_password
    users.clear();
    bool r = register_user("hank", "");
    bool l1 = login("hank", "");
    bool l2 = login("hank", "wrongpassword") == false;
    print_result("test_register_login_empty_password", r && l1 && l2);

    // test_long_password
    users.clear();
    std::string long_password(1000, 'a');
    bool reg = register_user("ida", long_password);
    bool l_ok = login("ida", long_password);
    bool l_wrong = login("ida", "shortpassword") == false;
    print_result("test_long_password", reg && l_ok && l_wrong);

    std::cout << "\nTests passed: " << passed << "\nTests failed: " << failed << "\n";

    return failed == 0 ? 0 : 1;
}
