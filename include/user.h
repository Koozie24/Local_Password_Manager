#include <string>

class User{
    private:
        std::string username;
        std::string password;
        std::string salt;
        std::string hash_result;
        std::string email;
    public:
        const std::string& getUsername() const {return username; }
        const std::string& getPassword() const {return password; }
        const std::string& getSalt() const {return salt; }
        const std::string& getHashresult() const {return hash_result; }
        const std::string& getEmail() const {return email; }

        User(std::string& username, std::string& password, std::string& email)
            : username(std::move(username)), password(std::move(password)), email(std::move(email)){
                //function to get salt
                //hash function
                //add to db function
            }

        //authentication function
        //reset pw function
};