#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <iostream>
#include "../include/session.h"
#include <fstream>

//established a connection to database when Session object is created
Session::Session(const std::string &db_host, const std::string &username, const std::string &password, const std::string &db_name){
    try{
        sql::Driver *driver = get_driver_instance();
        conn = std::shared_ptr<sql::Connection>(driver->connect(db_host, username, password));
        conn->setSchema(db_name); //equivalent to USE db name
        std::cout << "Connected to database: " << db_name << "\n";
    }
    catch(sql::SQLException &e){
        std::cerr << "Error connecting to database: " << e.what() << "\n";
        throw;
    }
}

std::shared_ptr<sql::Connection> Session::getConnection(){
    return conn;
}

std::string read_text_from_file(std::ifstream& file){
    std::string text, my_str;

    while(getline(file, my_str)){
        text += my_str;
    }
    return text;
}

void parse_string_for_account_info(std::string& text, Creds& credentials){

    int whitespace_found = 0, sep_found = 0;
    for(char c : text){
        if(c == ','){
            sep_found = 1;
            continue;
        }
        if(c == ' '){
            whitespace_found = 1;
            sep_found  = 0;
            continue;
        }
        if(sep_found && !whitespace_found){
            credentials.account += c;
        }
        else if(sep_found && whitespace_found){
            credentials.password += c;
        }
    }
}

void read_in_creds(std::string file_path, Creds& credentials){
    std::ifstream file(file_path);

    if(!file.is_open()){
        std::cerr<< "failed to open file at: " << file_path << "\n";
        exit(1);
    }

    std::string text = read_text_from_file(file);
    if(!text.length()){
        std::cerr << "Not able to read text at: " << file_path << "\n";
    }
    
    parse_string_for_account_info(text, credentials);
}