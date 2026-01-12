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

struct Creds {
        std::string account;
        std::string password;
    };

std::string read_text_from_file(std::ifstream& file);
void read_in_creds(std::string file_path, Creds& credentials);
void parse_string_for_account_info(std::string& text, Creds& credentials);
#endif