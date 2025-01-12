#include <iostream>
#include <algorithm>
#include <string>
#include <limits>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include "include/item.h"
#include "include/user.h"
#include "include/display.h"
#include "include/session.h"

/*Takes input from user until valid integer is recieved. Returns an int*/
int take_single_int_input(int number_of_options){
    int single_input;
    for(;;){
        std::cin >> single_input;
        if((number_of_options== 3 && single_input >= 1 && single_input <= 3) || //3 option
        (number_of_options == 4 && single_input >=1 && single_input <= 4)){ // 4 options
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //clear input buffer for getline
            break;
        }
        std::cout << "Sorry, that option is not valid. Try again from the options listed: ";
        std::cin.clear(); //reset cin state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //clear input buffer of invalid input
    }

    return single_input;
}

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

int main(){
    bool running = true;

    while(running){
        Session session("tcp://127.0.0.1:3306", "passmateadmin", "D1774%!f71pG", "passmate"); //initialize session
        
        std::string signed_in_user_name;
        bool current_session = false;
        clear_screen();
        display_start_screen(); //show sign in/create account options
        int start_screen_command = take_single_int_input(3); //take user command
        std::unique_ptr<sql::ResultSet> result_user;
        switch(start_screen_command){ //handling sign in screen
            case(1): //create account
                std::cout << "Creating an account.. " << std::endl; 
                break; 
            case(2): {  //account sign in scoped block
                while(!current_session){
                    clear_screen();
                    std::pair<std::string, std::string> login_string = display_sign_in_screen(); //show screen to input username
    
                    result_user = get_username(login_string.first, session.getConnection()); //get resulting user account info

                    if(result_user && result_user->next()){ //check not nullptr and result user returned something
                        if((login_string.first == result_user->getString("username"))
                         && (login_string.second == result_user->getString("password_hash"))){ //compare input to stored username and pass hash
                            signed_in_user_name = login_string.first;
                            current_session = true; //signed in is true
                        }
                    }
                    else{
                        std::cout << "Username or password is incorrect..." << std::endl;
                    }
                }
                break;
            }
            case(3): //exit program
                running = false;
                break;
        }

        while(current_session){ //while current user is signed in
            clear_screen();
            display_home_screen(signed_in_user_name);
                int home_screen_command = take_single_int_input(4);

                switch (home_screen_command){
                    case(1):
                        std::cout << "Looking up a credential.. " << std::endl; 
                        break;
                    case(2):
                        std::cout << "Adding a new credential.. " << std::endl; 
                        break;
                    case(3):
                        std::cout << "Browse existing Credentials.. " << std::endl; 
                        break;
                    case(4):
                        std::cout << "Sign-out of current session..." << std::endl;
                        current_session = false;
                        std::cout << "Exiting... " << std::endl;
                        break;
                }
        }
    }
    return 0;
}