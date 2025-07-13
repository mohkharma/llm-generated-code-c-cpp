#include <iostream>
#include <mysql/mysql.h>
#include <string>

void queryCustomerByUsername(const std::string& username) {
    MYSQL* conn;
    MYSQL_RES* res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "your_username", "your_password", "your_database", 0, NULL, 0)) {
        std::cout << "Error: " << mysql_error(conn) << std::endl;
        return;
    }

    std::string query = "SELECT * FROM customer WHERE customerusername = '" + username + "'";

    if (mysql_query(conn, query.c_str())) {
        std::cout << "Error: " << mysql_error(conn) << std::endl;
        mysql_close(conn);
        return;
    }

    res = mysql_store_result(conn);
    if (!res) {
        std::cout << "No result returned or error: " << mysql_error(conn) << std::endl;
        mysql_close(conn);
        return;
    }

    if ((row = mysql_fetch_row(res))) {
        unsigned int num_fields = mysql_num_fields(res);
        MYSQL_FIELD* fields = mysql_fetch_fields(res);
        for (unsigned int i = 0; i < num_fields; i++) {
            std::cout << fields[i].name << ": " << (row[i] ? row[i] : "NULL") << std::endl;
        }
    } else {
        std::cout << "Customer not found" << std::endl;
    }

    mysql_free_result(res);
    mysql_close(conn);
}
