#include <iostream>
#include <sqlite3.h>
#include <string>

void queryCustomerByUsername(const std::string& username) {
    sqlite3* db;
    int rc;

    rc = sqlite3_open("database.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    const char* sql = "SELECT * FROM customer WHERE customerusername = ?";

    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL prepare error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    rc = sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL bind error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return;
    }

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        int columnCount = sqlite3_column_count(stmt);
        for (int i = 0; i < columnCount; i++) {
            const char* columnName = sqlite3_column_name(stmt, i);
            const char* columnValue = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
            std::cout << columnName << ": " << (columnValue ? columnValue : "NULL") << std::endl;
        }
        std::cout << std::endl;
    } else if (rc == SQLITE_DONE) {
        std::cout << "No customer found with username: " << username << std::endl;
    } else {
        std::cerr << "SQL step error: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
