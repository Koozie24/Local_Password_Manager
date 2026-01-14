#include "../include/user.h"

void User::setRandomSalt(){
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
    salt = random_salt;
}

std::vector<unsigned char> User::hash_function(std::string plain_text){
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
void User::hash_password(const std::string& salt, const std::string& plain_password){
    std::string plain_text  = plain_password + salt; //concatenate password and salt
    
    std::vector<unsigned char> hash = hash_function(plain_text); //get back hashed char vector

    std::string final_hash;
    for(char c : hash){ //get hash as string
        final_hash += c; 
    }

    //return final_hash;

    setHashResult(final_hash);

}

/*Takes user object argument for account infomration, and a shared pointer to a connection to sql database. 
Tries to insert prepared statement to DB and outputs the error if unsuccessful.*/
void User::create_new_user(std::shared_ptr<sql::Connection> conn, const User& new_user){
    try{
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("INSERT INTO users (username, email, password_hash, salt) VALUES (?, ?, ?, ?)"));
        pstmt->setString(1, new_user.getUsername());
        std::cout << "\n You enterd user:" << new_user.getUsername();
        pstmt->setString(2, new_user.getEmail());
        std::cout << "\n You enterd email:" << new_user.getEmail();
        pstmt->setString(3, new_user.getHashResult());
        std::cout << "\n You enterd hash:" << new_user.getHashResult();
        pstmt->setString(4, new_user.getSalt());
        std::cout << "\n You enterd salt:" << new_user.getSalt();
        pstmt->executeUpdate();

        std::cout << "\n\n\n\nSuccessfully added use to table users in PASSMATE!";
    }
    catch(sql::SQLException &e){
        std::cerr << e.what() << std::endl;
    }

}