#include <httplib.h>
#include <sqlite3.h>
#include <nlohmann/json.hpp>
#include <iostream>

void startHttpUserServer() {
    httplib::Server svr;

    svr.Post("/user", [](const httplib::Request& req, httplib::Response& res) {
        try {
            auto json = nlohmann::json::parse(req.body);
            sqlite3* db;
            int rc = sqlite3_open("test.db", &db);
            if (rc) {
                res.status = 500;
                res.set_content("Database connection failed", "text/plain");
                return;
            }

            const char* createSQL = "CREATE TABLE IF NOT EXISTS users(id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, email TEXT)";
            char* errMsg = nullptr;
            rc = sqlite3_exec(db, createSQL, nullptr, 0, &errMsg);
            if (rc != SQLITE_OK) {
                res.status = 500;
                res.set_content("Failed to create table", "text/plain");
                sqlite3_free(errMsg);
                sqlite3_close(db);
                return;
            }

            std::string sql = "INSERT INTO users(name, email) VALUES(?, ?);";
            sqlite3_stmt* stmt = nullptr;
            rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
            if (rc != SQLITE_OK) {
                res.status = 500;
                res.set_content("SQL prepare failed", "text/plain");
                sqlite3_close(db);
                return;
            }

            sqlite3_bind_text(stmt, 1, json["name"].get<std::string>().c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 2, json["email"].get<std::string>().c_str(), -1, SQLITE_TRANSIENT);

            if (sqlite3_step(stmt) != SQLITE_DONE) {
                res.status = 500;
                res.set_content("Insert failed", "text/plain");
            } else {
                res.status = 200;
                res.set_content("User added successfully", "text/plain");
            }

            sqlite3_finalize(stmt);
            sqlite3_close(db);
        } catch (const std::exception& e) {
            res.status = 400;
            res.set_content(std::string("Invalid JSON: ") + e.what(), "text/plain");
        }
    });

    std::cout << "Server started on http://localhost:8080\n";
    svr.listen("localhost", 8080);
}
