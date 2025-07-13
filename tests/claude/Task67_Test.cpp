#include "../../source/output/claude/cpp/Task67_CLAUDE_claude-3-5-sonnet-20240620.cpp"

#include <iostream>
#include <string>
#include <cassert>
#include <fstream>
#include <sqlite3.h>

int tests_passed = 0;
int tests_failed = 0;

#define ASSERT_TRUE(cond) \
    if (cond) { \
        std::cout << "[PASS] " << __func__ << "\n"; \
        ++tests_passed; \
    } else { \
        std::cout << "[FAIL] " << __func__ << "\n"; \
        ++tests_failed; \
    }

void setup_database() {
    sqlite3* db;
    char* errMsg = nullptr;

    sqlite3_open("customer_database.db", &db);

    const char* create_table_sql =
        "DROP TABLE IF EXISTS customer;"
        "CREATE TABLE customer ("
        "id INTEGER PRIMARY KEY, "
        "customerusername TEXT, "
        "name TEXT, "
        "email TEXT, "
        "phone TEXT);";

    const char* insert_data_sql =
        "INSERT INTO customer VALUES "
        "(1, 'alice123', 'Alice Smith', 'alice@example.com', '123456789'),"
        "(2, 'bob456', 'Bob Jones', 'bob@example.com', '987654321');";

    sqlite3_exec(db, create_table_sql, nullptr, nullptr, &errMsg);
    sqlite3_exec(db, insert_data_sql, nullptr, nullptr, &errMsg);

    sqlite3_close(db);
}

void test_1_valid_username() {
    CustomerInfo* info = getCustomerInfo("alice123");
    ASSERT_TRUE(info != nullptr &&
                info->id == 1 &&
                info->username == "alice123" &&
                info->name == "Alice Smith" &&
                info->email == "alice@example.com" &&
                info->phone == "123456789");
    delete info;
}

void test_2_another_valid_username() {
    CustomerInfo* info = getCustomerInfo("bob456");
    ASSERT_TRUE(info != nullptr &&
                info->id == 2 &&
                info->username == "bob456" &&
                info->name == "Bob Jones" &&
                info->email == "bob@example.com" &&
                info->phone == "987654321");
    delete info;
}

void test_3_invalid_username() {
    CustomerInfo* info = getCustomerInfo("notfound");
    ASSERT_TRUE(info == nullptr);
}

void test_4_usage_message_not_supported() {
    std::cout << "Note: test_4_usage_message_not_supported not supported by this implementation.\n";
    ASSERT_TRUE(false);
}

void test_5_full_output_not_supported() {
    std::cout << "Note: test_5_full_output_not_supported not supported by this implementation.\n";
    ASSERT_TRUE(false);
}

int main() {
    setup_database();

    test_1_valid_username();
    test_2_another_valid_username();
    test_3_invalid_username();
    test_4_usage_message_not_supported();
    test_5_full_output_not_supported();

    std::cout << "\nTests Passed: " << tests_passed << "\n";
    std::cout << "Tests Failed: " << tests_failed << "\n";

    return tests_failed == 0 ? 0 : 1;
}
