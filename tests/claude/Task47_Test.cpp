#include "../../source/output/claude/cpp/Task47_CLAUDE_claude-3-5-sonnet-20240620.cpp"  // Include the header for the function

#include <iostream>
#include <sstream>
#include <fstream>      // ✅ ضروري لتفعيل ofstream
#include <vector>
#include <string>
#include <sqlite3.h>

int tests_passed = 0;
int tests_failed = 0;

// Helper: simulate a scrape using dummy HTML with <p> tags
void test_scrape_website() {
    std::string fakeHTML = R"(
        <html>
            <body>
                <p>Paragraph 1</p>
                <p>Paragraph 2</p>
                <p>Paragraph 3</p>
            </body>
        </html>
    )";

    // Save to local file and serve it using file:// URI
    std::ofstream htmlFile("test.html");
    htmlFile << fakeHTML;
    htmlFile.close();

    std::vector<std::string> expected = {"Paragraph 1", "Paragraph 2", "Paragraph 3"};
    std::vector<std::string> result = scrapeWebsite("file://test.html");

    if (result == expected) {
        std::cout << "[PASS] test_scrape_website\n";
        tests_passed++;
    } else {
        std::cout << "[FAIL] test_scrape_website\n";
        std::cout << "Expected: ";
        for (const auto& s : expected) std::cout << s << " | ";
        std::cout << "\nGot: ";
        for (const auto& s : result) std::cout << s << " | ";
        std::cout << "\n";
        tests_failed++;
    }
}

void test_store_in_database() {
    std::vector<std::string> sampleData = {"Paragraph 1", "Paragraph 2", "Paragraph 3"};
    std::string dbName = "scraped_data.db";

    storeInDatabase(sampleData);

    sqlite3* db;
    int rc = sqlite3_open(dbName.c_str(), &db);
    if (rc != SQLITE_OK) {
        std::cout << "[FAIL] test_store_in_database (cannot open db)\n";
        tests_failed++;
        return;
    }

    const char* sql = "SELECT content FROM scraped_text ORDER BY id;";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cout << "[FAIL] test_store_in_database (prepare failed)\n";
        tests_failed++;
        sqlite3_close(db);
        return;
    }

    std::vector<std::string> results;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char* text = sqlite3_column_text(stmt, 0);
        if (text)
            results.emplace_back(reinterpret_cast<const char*>(text));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    if (results == sampleData) {
        std::cout << "[PASS] test_store_in_database\n";
        tests_passed++;
    } else {
        std::cout << "[FAIL] test_store_in_database\n";
        std::cout << "Expected: ";
        for (const auto& s : sampleData) std::cout << s << " | ";
        std::cout << "\nGot: ";
        for (const auto& s : results) std::cout << s << " | ";
        std::cout << "\n";
        tests_failed++;
    }
}

int main() {
    test_scrape_website();
    test_store_in_database();

    std::cout << "\nTests passed: " << tests_passed << "\n";
    std::cout << "Tests failed: " << tests_failed << "\n";

    return tests_failed == 0 ? 0 : 1;
}
