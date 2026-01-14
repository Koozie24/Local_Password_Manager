#ifndef USER_H

#define USER_H

#include <string>
#include <cstdlib>
#include <openssl/evp.h>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

class User{
    public:
        //getter methods
        const std::string& getUsername() const {return username; }
        const std::string& getSalt() const {return salt; }
        const std::string& getHashResult() const {return hash_result; }
        const std::string& getEmail() const {return email; }
        const bool& getSignedInStatus() const {return user_is_signed_in; }
    
        //setter methods
        void setRandomSalt();
        void setUsername(std::string name) { username = name; }
        void setEmail(std::string addr){ email = addr; }
        void setHashResult(std::string result){ hash_result = result; }
        void setSignedInStatus(bool status) { user_is_signed_in = status; }

        //action methods
        std::vector<unsigned char> hash_function(std::string plain_text);
        void hash_password(const std::string& salt, const std::string& plain_password);
        void create_new_user(std::shared_ptr<sql::Connection> conn, const User& new_user);
        //authentication function
        //reset pw function

        User(std::string& username, std::string& password, std::string& email, std::shared_ptr<sql::Connection> conn){
            //: username(std::move(username)), password(std::move(password)), email(std::move(email)){
                setUsername(username);
                setEmail(email);
                setRandomSalt();
                hash_password(salt, password);
                create_new_user(conn, *this); //insert new user into DB UNCOMMENT WHEN READY TO TEST INSERTS
            }

        private:
            std::string username;
            //std::string password;
            std::string salt;
            std::string hash_result;
            std::string email;
            bool user_is_signed_in;
};

#endif