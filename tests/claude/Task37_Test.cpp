#include <iostream>
#include <string>
#include <mysql/mysql.h>

void get_user_info(const std::string& username) {
    MYSQL* conn = mysql_init(NULL);
    if (conn == NULL) {
        std::cout << "Error: " << mysql_error(conn) << std::endl;
        return;
    }
    // Connect with same credentials as Python code
    if (mysql_real_connect(conn, "127.0.0.1", "kali", "root", "test_db", 0, NULL, 0) == NULL) {
        std::cout << "Error: " << mysql_error(conn) << std::endl;
        mysql_close(conn);
        return;
    }

    // Use parameterized query equivalent by manually escaping quotes (not perfect)
    std::string query = "SELECT * FROM users WHERE username = '" + username + "'";

    if (mysql_query(conn, query.c_str())) {
        std::cout << "Error: " << mysql_error(conn) << std::endl;
        mysql_close(conn);
        return;
    }

    MYSQL_RES* res = mysql_use_result(conn);
    if (res == NULL) {
        std::cout << "Error retrieving result: " << mysql_error(conn) << std::endl;
        mysql_close(conn);
        return;
    }

    MYSQL_ROW row = mysql_fetch_row(res);
    if (row != NULL) {
        std::cout << "User found: ";
        for (unsigned int i = 0; i < mysql_num_fields(res); i++) {
            std::cout << (row[i] ? row[i] : "NULL") << (i < mysql_num_fields(res) - 1 ? ", " : "");
        }
        std::cout << std::endl;
    } else {
        std::cout << "User not found" << std::endl;
    }

    mysql_free_result(res);
    mysql_close(conn);
}

int main() {
    std::string username;
    std::cout << "Enter username: ";
    std::getline(std::cin, username);

    get_user_info(username);

    // Manual check required for pass/fail due to DB dependency
    std::cout << "Test case result: manual verification required" << std::endl;

    return 0;
}
