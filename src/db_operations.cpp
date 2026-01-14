#include <iostream>
#include <memory>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include "../include/db_operations.h"
#include "../include/user.h"

/*Takes a string argument of a username to search and a shared pointer to a connection to sql database.
substitutes username to a prepared statement and return a pointer to a result set*/
std::unique_ptr<sql::ResultSet> get_username(const std::string &search_name, std::shared_ptr<sql::Connection> conn){
    try{
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("SELECT * FROM users WHERE username = ?"));
        pstmt->setString(1, search_name);
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        return res;
    }
    catch(sql::SQLException &e){
        std::cerr << e.what() << "\n";
    }

    return nullptr;
}
