#include "../../source/output/claude/cpp/Task46_CLAUDE_claude-3-5-sonnet-20240620.cpp"
#include <iostream>
#include <sstream>
#include <string>
#include <sqlite3.h>

int testsPassed = 0;
int testsFailed = 0;

void assertTrue(bool condition, const std::string& testName) {
    if (condition) {
        std::cout << "[PASS] " << testName << "\n";
        ++testsPassed;
    } else {
        std::cout << "[FAIL] " << testName << "\n";
        ++testsFailed;
    }
}

// Helper to insert a user manually (simulate registerUser without I/O)
std::string registerUserDirect(sqlite3* db, const std::string& name, const std::string& email, const std::string& password) {
    std::string sql = "INSERT INTO users (name, email, password) VALUES (?, ?, ?);";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, email.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, password.c_str(), -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) == SQLITE_DONE) {
            sqlite3_finalize(stmt);
            return "Registration successful!";
        } else {
            sqlite3_finalize(stmt);
            return "Email already exists. Registration failed.";
        }
    } else {
        return "SQL error.";
    }
}

void test_register_new_user() {
    sqlite3* db;
    sqlite3_open(":memory:", &db);
    createTable(db);

    std::string result = registerUserDirect(db, "John Doe", "john@example.com", "password123");
    assertTrue(result.find("successful") != std::string::npos, "test_register_new_user");

    sqlite3_close(db);
}

void test_register_duplicate_email() {
    sqlite3* db;
    sqlite3_open(":memory:", &db);
    createTable(db);

    registerUserDirect(db, "John Doe", "john@example.com", "password123");
    std::string result = registerUserDirect(db, "Jane Doe", "john@example.com", "password456");

    assertTrue(result.find("Registration failed") != std::string::npos, "test_register_duplicate_email");

    sqlite3_close(db);
}

void test_create_table() {
    sqlite3* db;
    sqlite3_open(":memory:", &db);
    createTable(db);

    const char* sql = "SELECT name FROM sqlite_master WHERE type='table' AND name='users';";
    sqlite3_stmt* stmt;
    bool tableExists = false;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            tableExists = true;
        }
        sqlite3_finalize(stmt);
    }

    assertTrue(tableExists, "test_create_table");
    sqlite3_close(db);
}

void test_register_user_validity() {
    sqlite3* db;
    sqlite3_open(":memory:", &db);
    createTable(db);

    registerUserDirect(db, "Alice Smith", "alice@example.com", "password789");

    const char* sql = "SELECT * FROM users WHERE email = 'alice@example.com';";
    sqlite3_stmt* stmt;
    bool userExists = false;
    bool nameCorrect = false;
    bool emailCorrect = false;
    bool passCorrect = false;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            userExists = true;
            nameCorrect = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0))) == "Alice Smith";
            emailCorrect = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1))) == "alice@example.com";
            passCorrect = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2))) == "password789";
        }
        sqlite3_finalize(stmt);
    }

    assertTrue(userExists && nameCorrect && emailCorrect && passCorrect, "test_register_user_validity");
    sqlite3_close(db);
}

int main() {
    test_register_new_user();
    test_register_duplicate_email();
    test_create_table();
    test_register_user_validity();

    std::cout << "\nTests passed: " << testsPassed << "\n";
    std::cout << "Tests failed: " << testsFailed << "\n";

    return testsFailed == 0 ? 0 : 1;
}
