#include <iostream>
#include <sqlite3.h>
#include <string>
#include <cmath>

using namespace std;

const char* DB_PATH = "/home/kali/CLionProjects/llm-generated-code-cpp/tests/claude/Task137/products.db";

void createTable(sqlite3* db) {
    char* errMsg = 0;
    const char* sql = "CREATE TABLE IF NOT EXISTS products "
                      "(id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "name TEXT, "
                      "price REAL);";

    int rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
}

void addProduct(sqlite3* db, const string& name, double price) {
    sqlite3_stmt* stmt;
    const char* sql = "INSERT INTO products (name, price) VALUES (?, ?);";

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_double(stmt, 2, price);

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            cerr << "Execution failed: " << sqlite3_errmsg(db) << endl;
        }
    } else {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
    }
    sqlite3_finalize(stmt);
}

bool getProduct(sqlite3* db, int id, string& name_out, double& price_out) {
    sqlite3_stmt* stmt;
    const char* sql = "SELECT name, price FROM products WHERE id = ?;";

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, id);

        rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW) {
            name_out = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            price_out = sqlite3_column_double(stmt, 1);
            sqlite3_finalize(stmt);
            return true;
        } else {
            sqlite3_finalize(stmt);
            return false;
        }
    } else {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return false;
    }
}

bool test_add_and_get_product(sqlite3* db, const string& name, double price, int expected_id) {
    addProduct(db, name, price);
    string fetched_name;
    double fetched_price;
    bool found = getProduct(db, expected_id, fetched_name, fetched_price);
    if (!found) {
        cout << "Test add/get product ID " << expected_id << ": FAIL (not found)\n";
        return false;
    }
    bool pass = (fetched_name == name) && (fabs(fetched_price - price) < 1e-6);
    cout << "Test add/get product ID " << expected_id << ": " << (pass ? "PASS" : "FAIL") << "\n";
    if (!pass) {
        cout << "  Expected: (" << name << ", " << price << ")"
             << ", Got: (" << fetched_name << ", " << fetched_price << ")\n";
    }
    return pass;
}

bool test_get_nonexistent_product(sqlite3* db, int id) {
    string name;
    double price;
    bool found = getProduct(db, id, name, price);
    cout << "Test get non-existent product ID " << id << ": " << (!found ? "PASS" : "FAIL") << "\n";
    return !found;
}

int main() {
    sqlite3* db;
    int rc = sqlite3_open(DB_PATH, &db);

    if (rc) {
        cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
        return 1;
    }

    createTable(db);

    int pass_count = 0;
    int fail_count = 0;

    if (test_add_and_get_product(db, "Apple", 0.99, 1)) pass_count++; else fail_count++;
    if (test_add_and_get_product(db, "Banana", 1.50, 2)) pass_count++; else fail_count++;
    if (test_add_and_get_product(db, "Orange", 2.25, 3)) pass_count++; else fail_count++;

    {
        string name; double price;
        bool found = getProduct(db, 2, name, price);
        bool pass = found && (name == "Banana") && (fabs(price - 1.50) < 1e-6);
        cout << "Test get product ID 2: " << (pass ? "PASS" : "FAIL") << "\n";
        if (pass) pass_count++; else fail_count++;
    }

    if (test_get_nonexistent_product(db, 999)) pass_count++; else fail_count++;

    cout << "Summary: " << pass_count << " passed, " << fail_count << " failed.\n";

    sqlite3_close(db);
    return fail_count == 0 ? 0 : 1;
}
