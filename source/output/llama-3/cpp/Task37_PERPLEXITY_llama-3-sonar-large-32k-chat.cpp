// Task55_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp

#include <mysql/mysql.h>
#include <iostream>
#include <string>

void getUserByUsername(const std::string& username) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "your_username", "your_password", "test_db", 0, NULL, 0)) {
        std::cout << "Error connecting to database" << std::endl;
        return;
    }

    std::string query = "SELECT * FROM users WHERE username = '" + username + "'";
    if (mysql_query(conn, query.c_str())) {
        std::cout << "Error executing query" << std::endl;
        mysql_close(conn);
        return;
    }

    res = mysql_store_result(conn);
    if ((row = mysql_fetch_row(res)) != NULL) {
        std::cout << "User found: " << row[0] << ", " << row[1] << std::endl;
    } else {
        std::cout << "User not found" << std::endl;
    }

    mysql_free_result(res);
    mysql_close(conn);
}
