#include <iostream>
#include <sqlite3.h>
#include <string>
#include <cmath>

using namespace std;

class ProductDB {
    sqlite3* db = nullptr;
    string dbPath;

public:
    ProductDB(const string& path) : dbPath(path) {}

    bool open() {
        int rc = sqlite3_open(dbPath.c_str(), &db);
        if (rc) {
            cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
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
        char* errMsg = nullptr;
        const char* sql = "CREATE TABLE IF NOT EXISTS products "
                          "(id INTEGER PRIMARY KEY AUTOINCREMENT, "
                          "name TEXT, "
                          "price REAL);";

        int rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
        if (rc != SQLITE_OK) {
            cerr << "SQL error: " << errMsg << endl;
            sqlite3_free(errMsg);
        }
    }

    void clearTable() {
        char* errMsg = nullptr;
        const char* sql = "DELETE FROM products;";
        int rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
        if (rc != SQLITE_OK) {
            cerr << "SQL error clearing table: " << errMsg << endl;
            sqlite3_free(errMsg);
        }
    }

    bool addProduct(const string& name, double price) {
        sqlite3_stmt* stmt;
        const char* sql = "INSERT INTO products (name, price) VALUES (?, ?);";

        int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            cerr << "SQL error preparing insert: " << sqlite3_errmsg(db) << endl;
            return false;
        }

        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_double(stmt, 2, price);

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            cerr << "SQL error executing insert: " << sqlite3_errmsg(db) << endl;
            sqlite3_finalize(stmt);
            return false;
        }

        sqlite3_finalize(stmt);
        return true;
    }

    bool getProduct(int id, string& name_out, double& price_out) {
        sqlite3_stmt* stmt;
        const char* sql = "SELECT name, price FROM products WHERE id = ?;";

        int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            cerr << "SQL error preparing select: " << sqlite3_errmsg(db) << endl;
            return false;
        }

        sqlite3_bind_int(stmt, 1, id);

        rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW) {
            name_out = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            price_out = sqlite3_column_double(stmt, 1);
            sqlite3_finalize(stmt);
            return true;
        }

        sqlite3_finalize(stmt);
        return false;
    }
};

// ====== Test functions ======

bool test_add_and_get(ProductDB& pdb, const string& name, double price, int expected_id) {
    pdb.addProduct(name, price);
    string fetched_name;
    double fetched_price;
    bool found = pdb.getProduct(expected_id, fetched_name, fetched_price);
    if (!found) {
        cout << "Test add/get product ID " << expected_id << ": FAIL (not found)\n";
        return false;
    }
    bool pass = (fetched_name == name) && (fabs(fetched_price - price) < 1e-6);
    cout << "Test add/get product ID " << expected_id << ": " << (pass ? "PASS" : "FAIL") << "\n";
    if (!pass) {
        cout << "  Expected: (" << name << ", " << price << ")\n"
             << "  Got: (" << fetched_name << ", " << fetched_price << ")\n";
    }
    return pass;
}

bool test_get_nonexistent(ProductDB& pdb, int id) {
    string name;
    double price;
    bool found = pdb.getProduct(id, name, price);
    cout << "Test get non-existent product ID " << id << ": " << (!found ? "PASS" : "FAIL") << "\n";
    return !found;
}

// ====== Main ======

int main() {
    string dbPath = "/home/kali/CLionProjects/llm-generated-code-cpp/tests/gemini/Task137/products.db";

    ProductDB pdb(dbPath);
    if (!pdb.open()) {
        return 1;
    }

    pdb.createTable();
    pdb.clearTable();  // تنظيف البيانات قبل التست

    int pass_count = 0, fail_count = 0;

    if (test_add_and_get(pdb, "Apple", 0.99, 1)) pass_count++; else fail_count++;
    if (test_add_and_get(pdb, "Banana", 1.50, 2)) pass_count++; else fail_count++;
    if (test_add_and_get(pdb, "Orange", 2.25, 3)) pass_count++; else fail_count++;

    {
        string name; double price;
        bool found = pdb.getProduct(2, name, price);
        bool pass = found && (name == "Banana") && (fabs(price - 1.50) < 1e-6);
        cout << "Test get product ID 2: " << (pass ? "PASS" : "FAIL") << "\n";
        if (pass) pass_count++; else fail_count++;
    }

    if (test_get_nonexistent(pdb, 999)) pass_count++; else fail_count++;

    cout << "Summary: " << pass_count << " passed, " << fail_count << " failed.\n";

    pdb.close();
    return fail_count == 0 ? 0 : 1;
}
