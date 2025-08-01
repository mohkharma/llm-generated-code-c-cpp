#include <iostream>
#include <string>
#include <httplib.h>
#include <sqlite3.h>

void startUserApiServer() {
    sqlite3* db;
    char* zErrMsg = nullptr;
    int rc;

    // فتح قاعدة البيانات
    rc = sqlite3_open("users.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    } else {
        std::cout << "Opened database successfully" << std::endl;
    }

    // إنشاء جدول users إن لم يكن موجوداً
    const char* sqlCreateTable = R"(
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            email TEXT NOT NULL UNIQUE
        )
    )";

    rc = sqlite3_exec(db, sqlCreateTable, nullptr, nullptr, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return;
    }

    httplib::Server svr;

    // نقطة POST /users
    svr.Post("/users", [db](const httplib::Request& req, httplib::Response& res) {
        if (!req.has_param("name") || !req.has_param("email")) {
            res.status = 400;
            res.set_content("Name and email are required", "text/plain");
            return;
        }

        std::string name = req.get_param_value("name");
        std::string email = req.get_param_value("email");

        std::string sqlInsert = "INSERT INTO users (name, email) VALUES (?, ?)";
        sqlite3_stmt* stmt = nullptr;
        int rc = sqlite3_prepare_v2(db, sqlInsert.c_str(), -1, &stmt, nullptr);

        if (rc != SQLITE_OK) {
            res.status = 500;
            res.set_content("Failed to prepare SQL statement", "text/plain");
            return;
        }

        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, email.c_str(), -1, SQLITE_TRANSIENT);

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            const char* errMsg = sqlite3_errmsg(db);
            if (std::string(errMsg).find("UNIQUE constraint failed") != std::string::npos) {
                res.status = 400;
                res.set_content("Email already exists", "text/plain");
            } else {
                res.status = 500;
                res.set_content("Failed to create user", "text/plain");
                std::cerr << "SQL error: " << errMsg << std::endl;
            }
        } else {
            res.status = 201;
            res.set_content("User created successfully", "text/plain");
        }

        sqlite3_finalize(stmt);
    });

    std::cout << "Server started at http://localhost:8080\n";
    svr.listen("localhost", 8080);

    sqlite3_close(db);
}
