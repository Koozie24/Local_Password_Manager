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
        const bool& getSignedInStatus() const {return user_is_signed_in; }
    
        //setter methods
        void setSignedInStatus(bool status) { user_is_signed_in = status; }

        //action methods

        //authentication function
        //reset pw function

        //constructor for user object to sql db
        
        //constructor to create a signed in user
        User(std::string& username, bool active_session, std::shared_ptr<sql::Connection> conn){
            setSignedInStatus(active_session);
        }
        

        private:
            std::string username;
            bool user_is_signed_in;
};

#endif