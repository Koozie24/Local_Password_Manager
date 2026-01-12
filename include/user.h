#ifndef USER_H

#define USER_H

#include <string>
#include <cstdlib>
#include <openssl/evp.h>

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

        User(std::string& username, std::string& password, std::string& email, std::shared_ptr<sql::Connection> conn)
            : username(std::move(username)), password(std::move(password)), email(std::move(email)){
                salt = get_random_salt();

                hash_result = hash_password(salt, password);
                //create_new_user(conn, *this); //insert new user into DB UNCOMMENT WHEN READY TO TEST INSERTS
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

        /*Runs through SHA256 hashing algorithm and returns the hashed password as string
        Returns vector of unsigned chars https://wiki.openssl.org/index.php/EVP_Message_Digests*/
        std::vector<unsigned char> hash_function(std::string plain_text){
                unsigned char hash[EVP_MAX_MD_SIZE];
                unsigned int hash_length = 0;

                EVP_MD_CTX* mdctx = EVP_MD_CTX_new();

                if(mdctx == nullptr){ 
                    throw std::runtime_error("Failed to create EVP_MD_CTX_new");
                }
                if(1 != EVP_DigestInit_ex2(mdctx, EVP_sha256(), NULL) || 
                1 != EVP_DigestUpdate(mdctx, plain_text.c_str(), plain_text.length()) ||
                1 != EVP_DigestFinal_ex(mdctx, hash, &hash_length)){
                    EVP_MD_CTX_free(mdctx);
                    throw std::runtime_error("Failed to hash password"); //handle errors
                }

                EVP_MD_CTX_free(mdctx);

                return std::vector<unsigned char>(hash, hash + hash_length); //convert to vector of unsigned chars
        }

        /*Function takes two string arguments salt and a plain text password. */
        std::string hash_password(const std::string& salt, const std::string& plain_password){
                std::string plain_text  = plain_password + salt; //concatenate password and salt
                
                std::vector<unsigned char> hash = hash_function(plain_text); //get back hashed char vector

                std::string final_hash;
                for(char c : hash){ //get hash as string
                    final_hash += c; 
                }

                return final_hash;

        }

        /*Takes user object argument for account infomration, and a shared pointer to a connection to sql database. 
        Tries to insert prepared statement to DB and outputs the error if unsuccessful.*/
        void create_new_user(std::shared_ptr<sql::Connection> conn, const User& new_user){
            try{
                std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("INSERT INTO users (username, email, password_hash, salt) VALUES (?, ?, ?, ?)"));
                pstmt->setString(1, new_user.getUsername());
                pstmt->setString(2, new_user.getEmail());
                pstmt->setString(3, new_user.getHashresult());
                pstmt->setString(4, new_user.getSalt());
                pstmt->executeUpdate();
            }
            catch(sql::SQLException &e){
                std::cerr << e.what() << std::endl;
            }

        }
        //authentication function
        //reset pw function
};

#endif