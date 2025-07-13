
#include <iostream>
#include <string>
#include <sqlite3.h>

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

    if (sqlite3_open("customer_database.db", &db) == SQLITE_OK) {
        std::string sql = "SELECT * FROM customer WHERE customerusername = ?";
        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
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
