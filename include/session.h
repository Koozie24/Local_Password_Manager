#ifndef SESSION_H

#define SESSION_H

#include <cppconn/connection.h>
#include <cppconn/driver.h>
#include <memory>

class Session {
    private:
        std::shared_ptr<sql::Connection> conn;
    public:
        Session(const std::string &db_host, const std::string &username, const std::string &password, const std::string &db_name);
    
        std::shared_ptr<sql::Connection> getConnection(); //get database connection
};
#endif