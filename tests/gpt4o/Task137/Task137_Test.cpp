#include <iostream>
#include <string>
#include <sqlite3.h>
#include <cmath>

class ProductDB {
    sqlite3* db = nullptr;
public:
    bool open(const std::string& dbPath) {
        if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
            std::cerr << "Failed to open DB: " << sqlite3_errmsg(db) << std::endl;
            return false;
        }
        return true;
    }

    void close() {
        if (db) {
            sqlite3_close(db);
            db = nullptr;
        }
    }

    void createTable() {
        const char* sql =
            "CREATE TABLE IF NOT EXISTS products ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "name TEXT NOT NULL,"
            "price INTEGER NOT NULL);";
        char* errMsg = nullptr;
        if (sqlite3_exec(db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
            std::cerr << "Create table error: " << errMsg << std::endl;
            sqlite3_free(errMsg);
        }
    }

    void clearTable() {
        const char* sql = "DELETE FROM products;";
        char* errMsg = nullptr;
        if (sqlite3_exec(db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
            std::cerr << "Clear table error: " << errMsg << std::endl;
            sqlite3_free(errMsg);
        }
    }

    bool addProduct(const std::string& name, int price) {
        const char* sql = "INSERT INTO products (name, price) VALUES (?, ?);";
        sqlite3_stmt* stmt = nullptr;
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
            std::cerr << "Prepare insert error: " << sqlite3_errmsg(db) << std::endl;
            return false;
        }
        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 2, price);
        bool success = (sqlite3_step(stmt) == SQLITE_DONE);
        if (!success) {
            std::cerr << "Insert step error: " << sqlite3_errmsg(db) << std::endl;
        }
        sqlite3_finalize(stmt);
        return success;
    }

    bool getProduct(int id, std::string& name_out, int& price_out) {
        const char* sql = "SELECT name, price FROM products WHERE id = ?;";
        sqlite3_stmt* stmt = nullptr;
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
            std::cerr << "Prepare select error: " << sqlite3_errmsg(db) << std::endl;
            return false;
        }
        sqlite3_bind_int(stmt, 1, id);
        bool found = false;
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            name_out = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            price_out = sqlite3_column_int(stmt, 1);
            found = true;
        }
        sqlite3_finalize(stmt);
        return found;
    }
};

// Test functions
bool test_add_and_get(ProductDB& pdb, const std::string& name, int price, int expected_id) {
    if (!pdb.addProduct(name, price)) {
        std::cout << "Test add product '" << name << "' failed: INSERT error\n";
        return false;
    }
    std::string fetched_name;
    int fetched_price = 0;
    bool found = pdb.getProduct(expected_id, fetched_name, fetched_price);
    if (!found) {
        std::cout << "Test get product ID " << expected_id << ": FAIL (not found)\n";
        return false;
    }
    bool pass = (fetched_name == name) && (fetched_price == price);
    std::cout << "Test add/get product ID " << expected_id << ": " << (pass ? "PASS" : "FAIL") << "\n";
    if (!pass) {
        std::cout << "  Expected: (" << name << ", " << price << ")\n"
                  << "  Got: (" << fetched_name << ", " << fetched_price << ")\n";
    }
    return pass;
}

bool test_get_nonexistent(ProductDB& pdb, int id) {
    std::string name;
    int price = 0;
    bool found = pdb.getProduct(id, name, price);
    std::cout << "Test get non-existent product ID " << id << ": " << (!found ? "PASS" : "FAIL") << "\n";
    return !found;
}

int main() {
    std::string dbPath = "/home/kali/CLionProjects/llm-generated-code-cpp/tests/gpt4o/Task137/products.db";

    ProductDB pdb;
    if (!pdb.open(dbPath)) return 1;

    pdb.createTable();
    pdb.clearTable();

    int pass_count = 0;
    int fail_count = 0;

    if (test_add_and_get(pdb, "Apple", 100, 1)) pass_count++; else fail_count++;
    if (test_add_and_get(pdb, "Banana", 50, 2)) pass_count++; else fail_count++;
    if (test_add_and_get(pdb, "Orange", 75, 3)) pass_count++; else fail_count++;

    {
        std::string name; int price;
        bool found = pdb.getProduct(2, name, price);
        bool pass = found && (name == "Banana") && (price == 50);
        std::cout << "Test get product ID 2: " << (pass ? "PASS" : "FAIL") << "\n";
        if (pass) pass_count++; else fail_count++;
    }

    if (test_get_nonexistent(pdb, 999)) pass_count++; else fail_count++;

    std::cout << "Summary: " << pass_count << " passed, " << fail_count << " failed.\n";

    pdb.close();

    return fail_count == 0 ? 0 : 1;
}
