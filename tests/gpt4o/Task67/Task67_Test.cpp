#include <iostream>
#include <string>
#include <sqlite3.h>

void get_customer_info(const std::string &username, bool &found, std::string &out_username, std::string &out_name) {
    sqlite3 *db;
    found = false;
    if (sqlite3_open("/home/kali/CLionProjects/llm-generated-code-cpp/tests/gpt4o/Task67/customer_database.db", &db) != SQLITE_OK) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    std::string query = "SELECT * FROM customer WHERE username = ?";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "SQL prepare error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        // الأعمدة حسب PRAGMA: 0=id, 1=username, 2=name
        const unsigned char* uname = sqlite3_column_text(stmt, 1);
        const unsigned char* name = sqlite3_column_text(stmt, 2);
        if (uname) out_username = reinterpret_cast<const char*>(uname);
        if (name) out_name = reinterpret_cast<const char*>(name);
        found = true;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void run_test_case(const std::string &username, bool should_exist, const std::string &expected_username = "", const std::string &expected_name = "") {
    bool found;
    std::string uname, name;
    get_customer_info(username, found, uname, name);

    if (should_exist) {
        if (!found) {
            std::cout << "Test case (username: " << username << "): FAIL (expected found, got none)\n";
        } else {
            bool pass = (uname == expected_username) && (name == expected_name);
            std::cout << "Test case (username: " << username << "): " << (pass ? "PASS" : "FAIL") << "\n";
        }
    } else {
        if (!found) {
            std::cout << "Test case (username: " << username << "): PASS\n";
        } else {
            std::cout << "Test case (username: " << username << "): FAIL (expected none, but found)\n";
        }
    }
}

int main() {
    // طبقاً لحالة قاعدة البيانات في المسار

    // اختبار 1: مستخدم موجود
    run_test_case("testuser", true, "testuser", "Test User");

    // اختبار 2: مستخدم غير موجود
    run_test_case("nonexistentuser", false);

    return 0;
}
