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
        std::cerr << e.what() << std::endl;
    }

    return nullptr;
}

/*Takes four string arguments for account infomration, and a shared pointer to a connection to sql database. 
Tries to insert prepared statement to DB and outputs the error if unsuccessful.*/
void create_new_user(std::shared_ptr<sql::Connection> conn, const std::string &user_name, const std::string &password_hash, const std::string &salt, const std::string &email){
    try{
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("INSERT INTO users ('username', 'email', 'password_hash', 'salt) VALUES (?, ?, ?, ?)"));
        pstmt->setString(1, user_name);
        pstmt->setString(2, email);
        pstmt->setString(3, password_hash);
        pstmt->setString(4, salt);
        pstmt->executeUpdate();
    }
    catch(sql::SQLException &e){
        std::cerr << e.what() << std::endl;
    }

}