#include <string>
#include <cstdlib>

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
                salt = get_random_salt();
                //hash function
                //add to db function
            }


        std::string get_random_salt(){
            int salt_length = 8 + std::rand() % 4; //get a length of salt minimum 6 
            std::string random_salt;
            char lowercase_letter, special_character, uppercase_letter;\
            int random_digit;

            for(int i = 0; i < salt_length; i++){
                int what_type_of_char = rand() % 3;
                switch(what_type_of_char){
                    case(0):
                        lowercase_letter = 'a' + std::rand() % 26; //get random letter a to z
                        random_salt += lowercase_letter;
                        break;
                    case(1):
                        random_digit = std::rand() % 10; // get a random digit 0-9
                        random_salt += std::to_string(random_digit);
                        break;
                    case(2):
                        uppercase_letter = 'A' + std::rand() % 26;
                        random_salt += uppercase_letter;
                        break;
                }
            }
            return random_salt;
        }
        //authentication function
        //reset pw function
};