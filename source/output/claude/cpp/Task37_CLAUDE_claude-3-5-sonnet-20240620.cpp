#include <iostream>
#include <string>
#include <mysql/mysql.h>

void get_user_info(const std::string& username) {
    MYSQL* conn;
    MYSQL_RES* res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (conn == NULL) {
        std::cout << "Error: " << mysql_error(conn) << std::endl;
        return;
    }

if (mysql_real_connect(conn, "localhost", "kali", "", "test_db", 0, "/run/mysqld/mysqld.sock", 0) == NULL){
        std::cout << "Error: " << mysql_error(conn) << std::endl;
        mysql_close(conn);
        return;
    }

    std::cout << "Connected successfully\n";  // Debug

    std::string query = "SELECT * FROM users WHERE username = '" + username + "'";
    if (mysql_query(conn, query.c_str())) {
        std::cout << "Error: " << mysql_error(conn) << std::endl;
        mysql_close(conn);
        return;
    }

    res = mysql_store_result(conn);  // ✅ استخدم store بدل use
    if ((row = mysql_fetch_row(res)) != NULL) {
        std::cout << "User found: " << row[0] << std::endl;
    } else {
        std::cout << "User not found" << std::endl;
    }

    mysql_free_result(res);
    mysql_close(conn);
}
