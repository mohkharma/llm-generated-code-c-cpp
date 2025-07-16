#include <iostream>
#include <sqlite3.h>
#include <string>

bool queryCustomerByUsername(const std::string& username) {
    sqlite3* db;
    sqlite3_stmt* stmt;
    int rc;

    rc = sqlite3_open("/home/kali/CLionProjects/llm-generated-code-cpp/tests/llama-3/Task67/customer_database.db", &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    std::string sql = "SELECT * FROM customer WHERE username = ?";

    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL prepare error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return false;
    }

    rc = sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL bind error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return false;
    }

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        int columnCount = sqlite3_column_count(stmt);
        std::cout << "Customer Information:\n";
        for (int i = 0; i < columnCount; ++i) {
            const char* columnName = sqlite3_column_name(stmt, i);
            const char* columnValue = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
            std::cout << columnName << ": " << (columnValue ? columnValue : "NULL") << std::endl;
        }
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return true;
    } else if (rc == SQLITE_DONE) {
        std::cout << "Customer not found." << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return false;
    } else {
        std::cerr << "SQL step error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return false;
    }
}

void run_test_case(const std::string& username, bool should_exist) {
    bool found = queryCustomerByUsername(username);
    std::cout << "Test case (username: " << username << "): " << (found == should_exist ? "PASS" : "FAIL") << std::endl;
}

int main() {
    // نفس التست كيسز البايثون
    run_test_case("testuser", true);
    run_test_case("nonexistentuser", false);

    return 0;
}
