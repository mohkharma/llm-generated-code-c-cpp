#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "../../../source/output/gemini/cpp/Task122_GEMINI_gemini-1.5-pro-001.cpp"

void clear_file(const std::string& filename) {
    std::ofstream(filename, std::ios::trunc).close();
}

bool username_exists(const std::string& filename, const std::string& username) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        if (username.empty()) {
            if (line.rfind(":", 0) == 0) return true;
        } else {
            if (line.find(username + ":") == 0) return true;
        }
    }
    return false;
}

bool file_contains_plain_password(const std::string& filename, const std::string& password) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        if (line.find(password) != std::string::npos) return true;
    }
    return false;
}

bool test_case(const std::string& title, const std::string& username, const std::string& password) {
    std::cout << title << std::endl;

    std::stringstream input;
    input << username << "\n" << password << "\n";

    std::streambuf* orig_cin = std::cin.rdbuf();
    std::cin.rdbuf(input.rdbuf());

    signup();

    std::cin.rdbuf(orig_cin);

    bool success = true;

    if (!username_exists("users.txt", username)) {
        std::cout << "❌ Username not stored: \"" << username << "\"\n";
        success = false;
    }
    if (file_contains_plain_password("users.txt", password)) {
        std::cout << "❌ Password stored in plain text!\n";
        success = false;
    }

    if (success) {
        std::cout << "✅ Test passed\n";
    }

    std::cout << "----------------------\n";
    return success;
}

int main() {
    clear_file("users.txt");

    int passed = 0, failed = 0;

    auto run = [&](const std::string& title, const std::string& username, const std::string& password) {
        if (test_case(title, username, password)) ++passed;
        else ++failed;
    };

    run("Test 1: Normal Signup", "user1", "password123");
    run("Test 2: Special Username", "user!@#", "password123");
    run("Test 3: Special Password", "user2", "pa$$w0rd!");
    run("Test 4: Empty Username", "", "password123");
    run("Test 5: Empty Password", "user3", "");
    run("Test 6: Long Username and Password", std::string(100, 'u'), std::string(100, 'p'));
    run("Test 7A: Multiple Users", "user4", "pass1");
    run("Test 7B: Multiple Users", "user5", "pass2");
    run("Test 8A: Duplicate Username", "user6", "firstpass");
    run("Test 8B: Duplicate Username Overwrite", "user6", "secondpass");
    run("Test 10: Null-like Characters", "user\0name", "pass\0word");
    run("Test 11A: Duplicate Entry", "user8", "dup1");
    run("Test 11B: Duplicate Entry Again", "user8", "dup2");
    run("Test 12: Very Long Data", std::string(1000, 'x'), std::string(1000, 'y'));
    for (int i = 0; i < 10; ++i) {
        run("Test 13: File Capacity Sim " + std::to_string(i), "user" + std::to_string(i), "pass123");
    }
    run("Test 17: Dotted Username", "user.with.many.extensions", "p@ss");

    std::cout << "\n✅ Passed: " << passed << "\n❌ Failed: " << failed << std::endl;

    return failed == 0 ? 0 : 1;
}
