#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <iostream>
#include "include/session.h"

//established a connection to database when Session object is created
Session::Session(const std::string &db_host, const std::string &username, const std::string &password, const std::string &db_name){
    try{
        sql::Driver *driver = get_driver_instance();
        conn = std::shared_ptr<sql::Connection>(driver->connect(db_host, username, password));
        conn->setSchema(db_name); //equivalent to USE db name
        std::cout << "Connected to database: " << db_name << std::endl;
    }
    catch(sql::SQLException &e){
        std::cerr << "Error connecting to database: " << e.what() << std::endl;
        throw;
    }
}

std::shared_ptr<sql::Connection> Session::getConnection(){
    return conn;
}