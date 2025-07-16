#include <iostream>
#include <sqlite3.h>
#include <string>

using namespace std;

struct Customer {
    string customerusername;
    string customerfirstname;
    // Add other fields if needed
    bool is_empty = true; // لمعرفه اذا وجد بيانات فعلاً
};

Customer get_customer_info(const string& customerusername) {
    sqlite3* db;
    sqlite3_stmt* stmt;
    int rc;
    Customer customer;

    rc = sqlite3_open("/home/kali/CLionProjects/llm-generated-code-cpp/tests/codestral/Task67/customer_database.db", &db);
    if (rc != SQLITE_OK) {
        cerr << "Cannot open database: " << sqlite3_errmsg(db) << endl;
        return customer; // empty customer
    }

    string sql ="SELECT * FROM customer WHERE username = ?";

    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return customer; // empty customer
    }

    sqlite3_bind_text(stmt, 1, customerusername.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        customer.customerusername = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)); // username
        customer.customerfirstname = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)); // name
        customer.is_empty = false;
    }


    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return customer;
}

// اختبار مساعدة للمقارنة وطباعة النتائج
void run_test_case(const string& username, bool should_exist, const Customer& expected = {}) {
    Customer c = get_customer_info(username);

    if (should_exist) {
        if (c.is_empty) {
            cout << "Test case (username: " << username << "): FAIL (expected found, got none)\n";
        } else {
            bool pass = (c.customerusername == expected.customerusername) &&
                        (c.customerfirstname == expected.customerfirstname);
            cout << "Test case (username: " << username << "): " << (pass ? "PASS" : "FAIL") << "\n";
        }
    } else {
        if (c.is_empty) {
            cout << "Test case (username: " << username << "): PASS\n";
        } else {
            cout << "Test case (username: " << username << "): FAIL (expected none, but found)\n";
        }
    }
}

int main() {
    // مثال اختبار - عدل القيم حسب بيانات قاعدة البيانات الحقيقية

    // اختبار 1: مستخدم موجود
    Customer expected1;
    expected1.customerusername = "testuser";
    expected1.customerfirstname = "Test User"; // عدل حسب القاعدة

    run_test_case("testuser", true, expected1);

    // اختبار 2: مستخدم غير موجود
    run_test_case("nonexistentuser", false);

    return 0;
}
