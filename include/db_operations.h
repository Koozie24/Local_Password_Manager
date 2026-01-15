#ifndef DB_OPERATIONS_H

#define DB_OPERATIONS_H
#include <string>
#include <cstdlib>
#include <openssl/evp.h>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include "inputs.h"

class Account{
    public:
    //getters
        const std::string& getAccount() { return account_name; }
        const std::string& getEmail() { return email; }
        const std::string& getHash() { return hash; }
        const std::string& getSalt() { return salt; }
        const bool& getUserExists() { return user_exists; }
        const bool& getAccountCreatedStatus() { return account_was_created; }

    //setters
        void setAccount(std::string account) { account_name = account; }
        void setEmail(std::string email_str) { email = email_str; }
        void setHash(std::string hash_str) { hash = hash_str; }
        void setSalt(std::string salt_str) { salt = salt_str; }
        void setRandomSalt();
        void setAccountCreation(bool t_f_val) {account_was_created = t_f_val; }

    //action methods
    std::vector<unsigned char> hash_function(std::string plain_text);
    std::string hash_password(const std::string& salt, const std::string& plain_password);
    void checkUsernameExists(const std::string &search_name, std::shared_ptr<sql::Connection> conn);
    void createNewAccount(std::shared_ptr<sql::Connection> conn);

    //constructor for account creation
    Account(std::string& name, std::string& email, std::string& password_str, std::shared_ptr<sql::Connection> conn){
        checkUsernameExists(name, conn);

        //if no user currently in table, hash password 
        if(!user_exists){
            setAccount(name);
            setEmail(email);
            setRandomSalt();

            std::string ret_hash = hash_password(salt, password_str);
            setHash(ret_hash);
            createNewAccount(conn);
        }
        else { account_was_created = false; }
    }

    //sign in constructor
    Account(std::string &name, std::shared_ptr<sql::Connection> conn){
        checkUsernameExists(name, conn);
        if(user_exists){
            setAccount(name);
        }
    }

    private:
        std::string account_name;
        std::string email;
        std::string hash;
        std::string salt;
        bool user_exists;
        bool account_was_created;
};





class Authentication : public Account{
    public:
        //setter
            void setAuthStatus(bool &val) { authentication_status = val; }
            void setExtractStatus(bool &val) { extract_hash_n_salt_success = val; }
            void setLoginAttemptsRemaining() { login_attempts_remaining = 3; }
            void decrementLoginAttemptsRemaining() { login_attempts_remaining--; }
            void setInputHash(std::string hash_str) { input_pwd_hash = hash_str; }

        //getter
            const bool getAuthStatus() { return authentication_status; }
            const bool getExtractStatus() { return extract_hash_n_salt_success; }
            const int getAttemptsRemaining() { return login_attempts_remaining; }
            const std::string& getInputHash() { return input_pwd_hash; }

        //other methods
            void fetchEntryFromDb(const std::string &search_name, std::shared_ptr<sql::Connection> conn);
            void setValuesFromDbFetch();
            bool checkClearToAttemptAuth();
            bool compareHashValues(const std::string &password_str_input);

        //constructor
            Authentication(std::string& acct_name, std::shared_ptr<sql::Connection> conn) : Account(acct_name, conn){
                if(this->getUserExists()){
                    fetchEntryFromDb(this->getAccount(), conn);
                    setValuesFromDbFetch(); //before using these vals we want to check extract status and user exists
                }   
            }
    private:
        bool authentication_status;
        bool extract_hash_n_salt_success;
        std::unique_ptr<sql::ResultSet> fetched_entry;
        int login_attempts_remaining;
        std::string input_pwd_hash;
};
#endif