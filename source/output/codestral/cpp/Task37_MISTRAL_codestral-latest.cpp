#include <mysql_driver.h>
#include <mysql_connection.h>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include <iostream>
#include <string>

void queryUserByUsername() {
    try {
        sql::Driver* driver = sql::mysql::get_driver_instance();
        std::unique_ptr<sql::Connection> con(driver->connect("tcp://127.0.0.1:3306", "kali", ""));
        con->setSchema("test_db");

        std::string username;
        std::cout << "Enter username: ";
        std::getline(std::cin, username);

        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT * FROM users WHERE username = ?"));
        pstmt->setString(1, username);

        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        if (res->next()) {
            std::cout << "User found: " << res->getString("username") << std::endl;
        } else {
            std::cout << "User not found" << std::endl;
        }
    } catch (const sql::SQLException& e) {
        std::cerr << "# ERR: SQLException in " << __FILE__
                  << "(" << __func__ << ") on line " << __LINE__ << std::endl;
        std::cerr << "# ERR: " << e.what() << " (MySQL error code: " << e.getErrorCode()
                  << ", SQLState: " << e.getSQLState() << ")" << std::endl;
    }
}
