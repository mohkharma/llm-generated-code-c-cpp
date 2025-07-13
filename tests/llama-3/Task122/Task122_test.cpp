#include <iostream>
#include <sstream>
#include <string>
#include <map>

#include "../../../source/output/llama-3/cpp/Task122_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"

bool user_exists(const std::string& username, const std::string& password) {
    auto it = users.find(username);
    if (it != users.end()) {
        return it->second.password == password;
    }
    return false;
}

void clear_users() {
    users.clear();
}

bool test_case(const std::string& title, const std::string& username, const std::string& password) {
    std::cout << title << std::endl;

    std::stringstream input;
    input << username << "\n" << password << "\n";

    std::streambuf* orig_cin = std::cin.rdbuf();
    std::cin.rdbuf(input.rdbuf());

    try {
        signup();
    } catch (...) {
        std::cerr << "❌ Exception during signup()\n";
        std::cin.rdbuf(orig_cin);
        return false;
    }

    std::cin.rdbuf(orig_cin);

    if (user_exists(username, password)) {
        std::cout << "✅ Test passed\n";
        std::cout << "----------------------\n";
        return true;
    } else {
        std::cout << "❌ User not stored correctly\n";
        std::cout << "----------------------\n";
        return false;
    }
}

int main() {
    clear_users();

    int passed = 0, failed = 0;

    auto run = [&](const std::string& title, const std::string& username, const std::string& password) {
        if (test_case(title, username, password)) ++passed;
        else ++failed;
    };

    run("Test Case 1: Normal Signup", "user1", "password123");
    run("Test Case 2: Special Username", "user!@#", "password123");
    run("Test Case 3: Special Password", "user2", "pa$$w0rd!");
    run("Test Case 4: Empty Username", "", "password123");
    run("Test Case 5: Empty Password", "user3", "");
    run("Test Case 6: Long Username and Password", std::string(100, 'u'), std::string(100, 'p'));
    run("Test Case 7A: Multiple Users", "user4", "pass1");
    run("Test Case 7B: Multiple Users", "user5", "pass2");
    run("Test Case 8A: Duplicate Username", "user6", "firstpass");
    run("Test Case 8B: Duplicate Username Overwrite", "user6", "secondpass");
    run("Test Case 10: Null-like Characters", "user\0name", "pass\0word");
    run("Test Case 11A: Duplicate Entry", "user8", "password6");
    run("Test Case 11B: Duplicate Entry Again", "user8", "password6");
    run("Test Case 12: Very Long Data", std::string(1000, 'u'), std::string(1000, 'y'));
    for (int i = 0; i < 10; ++i) {
        run("Test 13: Bulk user " + std::to_string(i), "user" + std::to_string(i), "password123");
    }
    run("Test Case 17: Dotted Username", "user.with.many.extensions", "password");
    run("Test Case 18: Security Measures", "user11", "password11");
    run("Test Case 19: Exception Handling", "user12", "password12");

    std::cout << "\n✅ Passed: " << passed << "\n❌ Failed: " << failed << std::endl;
    return failed == 0 ? 0 : 1;
}
