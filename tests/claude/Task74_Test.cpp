#include "../../source/output/claude/cpp/Task74_CLAUDE_claude-3-5-sonnet-20240620.cpp"  // createConnection
#include <iostream>

int passed = 0, failed = 0;

void print_result(const std::string& name, bool ok) {
    std::cout << (ok ? "[PASS] " : "[FAIL] ") << name << "\n";
    (ok ? ++passed : ++failed);
}

void test_successful_connection() {
    pqxx::connection* conn = createConnection();
    bool ok = (conn != nullptr && conn->is_open());
    print_result("Successful connection", ok);
    if (conn) {
        delete conn;
    }
}

void test_reuse_connection() {
    pqxx::connection* conn1 = createConnection();
    pqxx::connection* conn2 = createConnection();
    bool ok = (conn1 != nullptr && conn2 != nullptr && conn1 != conn2);
    print_result("Multiple separate connections", ok);
    if (conn1) delete conn1;
    if (conn2) delete conn2;
}

void test_manual_close_check() {
    pqxx::connection* conn = createConnection();
    bool ok = (conn != nullptr && conn->is_open());
    print_result("Manual delete and is_open check (prior)", ok);
    if (conn) delete conn;
}

void test_double_delete_safety() {
    pqxx::connection* conn = createConnection();
    bool ok = false;
    if (conn) {
        try {
            delete conn;
            // Do not delete again — double-delete is undefined behavior, so we avoid it
            ok = true;
        } catch (...) {
            ok = false;
        }
    }
    print_result("Safe delete without crash", ok);
}

void test_connection_failure_simulation() {
    try {
        pqxx::connection bad_conn("host=invalid_host dbname=wrong user=none password=fail");
        print_result("Simulated bad connection", false);  // Should not reach here
    } catch (const std::exception& e) {
        print_result("Simulated bad connection", true);
    }
}

int main() {
    test_successful_connection();
    test_reuse_connection();
    test_manual_close_check();
    test_double_delete_safety();
    test_connection_failure_simulation();

    std::cout << "\nSummary: " << passed << " passed, " << failed << " failed.\n";
    return failed == 0 ? 0 : 1;
}
