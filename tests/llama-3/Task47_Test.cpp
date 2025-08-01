#include <iostream>
#include <vector>
#include <string>
#include <sqlite3.h>
#include <cstdio>  // for remove()

#include "../../source/output/gpt4o/cpp/Task47_OPENAI_gpt-4o.cpp"

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

// test_scrape_website: التأكد من أن scrapeData تستخرج العناصر الصحيحة
void test_scrape_website() {
    std::vector<std::string> expected = {"Paragraph 1", "Paragraph 2", "Paragraph 3"};

    // نستخدم ملف HTML محلي لأن الموقع غير ثابت أثناء الاختبار
    const std::string fakeHTML = R"(
        <html><body><ul>
            <li>Paragraph 1</li>
            <li>Paragraph 2</li>
            <li>Paragraph 3</li>
        </ul></body></html>
    )";

    // نكتب الملف إلى قرص مؤقتًا ونمرره عبر file://
    const std::string path = "test_file.html";
    FILE* f = fopen(path.c_str(), "w");
    fputs(fakeHTML.c_str(), f);
    fclose(f);

    std::vector<std::string> result = scrapeData("file://" + path);

    remove(path.c_str());  // حذف الملف

    printResult("test_scrape_website", result == expected);
}

// test_store_in_database: التأكد من أن storeData تخزن البيانات فعليًا
void test_store_in_database() {
    const std::string dbPath = "test.db";
    std::remove(dbPath.c_str());  // حذف قاعدة البيانات القديمة

    std::vector<std::string> data = {"Paragraph 1", "Paragraph 2", "Paragraph 3"};
    storeData(dbPath, data);

    // التأكد من أن البيانات موجودة فعليًا
    sqlite3* db;
    int rc = sqlite3_open(dbPath.c_str(), &db);
    if (rc != SQLITE_OK) {
        printResult("test_store_in_database", false);
        return;
    }

    const char* sql = "SELECT content FROM scraped_data ORDER BY rowid;";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    std::vector<std::string> result;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const char* text = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        result.emplace_back(text);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    std::remove(dbPath.c_str());

    printResult("test_store_in_database", result == data);
}

int main() {
    test_scrape_website();
    test_store_in_database();

    std::cout << "\nTotal Passed: " << testsPassed << "\n";
    std::cout << "Total Failed: " << testsFailed << "\n";

    return testsFailed == 0 ? 0 : 1;
}
