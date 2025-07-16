#include <iostream>
#include <sqlite3.h>
#include <string>

const char* DB_PATH = "/home/kali/CLionProjects/llm-generated-code-cpp/tests/codestral/Task67/customer_database.db";

struct CustomerInfo {
    int id;
    std::string username;
    std::string name;
    std::string email;
    std::string phone;
};

CustomerInfo* getCustomerInfo(const std::string& username) {
    sqlite3* db;
    sqlite3_stmt* stmt;
    CustomerInfo* customer = nullptr;

    if (sqlite3_open(DB_PATH, &db) == SQLITE_OK) {
        const char* sql = "SELECT * FROM customer WHERE username = ?";
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

            if (sqlite3_step(stmt) == SQLITE_ROW) {
                customer = new CustomerInfo;
                customer->id = sqlite3_column_int(stmt, 0);
                customer->username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
                customer->name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
                customer->email = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
                customer->phone = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
            }
            sqlite3_finalize(stmt);
        }
        sqlite3_close(db);
    }
    return customer;
}

// دالة مساعدة لمقارنة النصوص
bool equals(const std::string& a, const std::string& b) {
    return a == b;
}

void run_test_case(const std::string& username, bool should_exist, CustomerInfo expected = {}) {
    CustomerInfo* c = getCustomerInfo(username);
    if (should_exist) {
        if (c == nullptr) {
            std::cout << "Test case (username: " << username << "): FAIL (not found but expected)\n";
        } else {
            bool pass = (c->username == expected.username) &&
                        (c->name == expected.name) &&
                        (c->email == expected.email) &&
                        (c->phone == expected.phone);
            std::cout << "Test case (username: " << username << "): " << (pass ? "PASS" : "FAIL") << "\n";
        }
    } else {
        if (c == nullptr) {
            std::cout << "Test case (username: " << username << "): PASS\n";
        } else {
            std::cout << "Test case (username: " << username << "): FAIL (found but not expected)\n";
        }
    }
    delete c;
}

int main() {
    // Test cases based exactly on python code scenarios

    // Test case 1: existing user (you must update expected values as per your db)
    CustomerInfo expected1 = {1, "testuser", "Test User", "testuser@example.com", "1234567890"};
    run_test_case("testuser", true, expected1);

    // Test case 2: non-existing user
    run_test_case("nonexistentuser", false);

    return 0;
}
