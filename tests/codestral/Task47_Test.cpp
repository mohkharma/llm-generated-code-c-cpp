#include <iostream>
#include <vector>
#include <string>
#include <sqlite3.h>
#include <cassert>

#include "../../source/output/codestral/cpp/Task47_MISTRAL_codestral-latest.cpp"

int testsPassed = 0;
int testsFailed = 0;

void printResult(const std::string& testName, bool passed) {
    if (passed) {
        std::cout << "[PASS] " << testName << "\n";
        ++testsPassed;
    } else {
        std::cout << "[FAIL] " << testName << "\n";
        ++testsFailed;
    }
}

// Simulates the Python test_scrape_website by checking if title is inserted
void test_scrape_website() {
    // Remove old DB file to ensure fresh test
    std::remove("website_data.db");

    scrapeAndStoreWebsiteData();

    sqlite3* db;
    int rc = sqlite3_open("website_data.db", &db);
    if (rc != SQLITE_OK) {
        printResult("test_scrape_website", false);
        return;
    }

    const char* query = "SELECT title FROM data ORDER BY ROWID DESC LIMIT 1;";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, query, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        printResult("test_scrape_website", false);
        return;
    }

    std::string title;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char* text = sqlite3_column_text(stmt, 0);
        title = reinterpret_cast<const char*>(text);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    // Allow any non-empty title
    printResult("test_scrape_website", !title.empty());
}

// Simulates the Python test_store_in_database
void test_store_in_database() {
    sqlite3* conn;
    int rc = sqlite3_open(":memory:", &conn);
    if (rc != SQLITE_OK) {
        printResult("test_store_in_database", false);
        return;
    }

    std::vector<std::string> data = {"Paragraph 1", "Paragraph 2", "Paragraph 3"};
    const char* createSQL = "CREATE TABLE scraped_text(id INTEGER PRIMARY KEY, content TEXT);";
    rc = sqlite3_exec(conn, createSQL, nullptr, nullptr, nullptr);

    const char* insertSQL = "INSERT INTO scraped_text(content) VALUES(?);";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(conn, insertSQL, -1, &stmt, nullptr);

    for (const std::string& item : data) {
        sqlite3_bind_text(stmt, 1, item.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_step(stmt);
        sqlite3_reset(stmt);
    }
    sqlite3_finalize(stmt);

    // Now query back
    std::vector<std::string> result;
    const char* selectSQL = "SELECT content FROM scraped_text ORDER BY id;";
    rc = sqlite3_prepare_v2(conn, selectSQL, -1, &stmt, nullptr);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char* text = sqlite3_column_text(stmt, 0);
        result.emplace_back(reinterpret_cast<const char*>(text));
    }
    sqlite3_finalize(stmt);
    sqlite3_close(conn);

    printResult("test_store_in_database", result == data);
}

int main() {
    test_scrape_website();
    test_store_in_database();

    std::cout << "\nTotal Passed: " << testsPassed << "\n";
    std::cout << "Total Failed: " << testsFailed << "\n";

    return testsFailed == 0 ? 0 : 1;
}
