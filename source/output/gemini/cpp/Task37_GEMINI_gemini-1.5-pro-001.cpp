#include <iostream>
#include <string>
#include <sqlite3.h>

void queryUserFromSQLite() {
    sqlite3* db;
    char* zErrMsg = nullptr;
    int rc;

    rc = sqlite3_open("your_database.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    std::string username;
    std::cout << "Enter username: ";
    std::cin >> username;

    std::string sql = "SELECT * FROM users WHERE username='" + username + "'";
    const char* query = sql.c_str();

    rc = sqlite3_exec(db, query, [](void* data, int argc, char** argv, char** azColName) -> int {
        for (int i = 0; i < argc; ++i) {
            std::cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << std::endl;
        }
        std::cout << std::endl;
        return 0;
    }, nullptr, &zErrMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }

    sqlite3_close(db);
}
