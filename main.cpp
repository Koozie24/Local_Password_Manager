#include <iostream>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <ctime>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include "include/item.h"
#include "include/user.h"
#include "include/display.h"
#include "include/session.h"
#include "include/inputs.h"
#include "include/db_operations.h"

bool check_password_complexity(const std::string& password){
    bool number = false;
    bool upperletter = false;
    bool lowerletter = false;
    bool special_char = false;
    int length_of_pw = password.length();
    bool requirements_met = false;

     for(char c : password){
        //convert current char to ordinal value and check against ranges of values if given flag is false
        int ordinal_value_of_char = static_cast<int>(c);

        if(ordinal_value_of_char >= 97 && ordinal_value_of_char <= 122 && lowerletter == false){
            lowerletter = true;
        }
        if(ordinal_value_of_char >= 65 && ordinal_value_of_char <= 90 && upperletter == false){
            upperletter = true;
        }
        if(ordinal_value_of_char >= 48 && ordinal_value_of_char <= 57 && number == false){
            number = true;
        }
        if(ordinal_value_of_char >= 32 && ordinal_value_of_char <= 47 && special_char == false){
            special_char = true;
        }
     }

     if(number == true && upperletter == true && lowerletter == true && special_char == true && length_of_pw >= 10){
        requirements_met = true; //password requirements are met
     }

     return requirements_met;
}

bool check_valid_email(const std::string& email){
    bool is_valid_email = false;
    bool contain_at_symbol = false;
    bool contains_valid_dot = false;

    for(char c : email){
        if(c == '@'){ 
            contain_at_symbol = true;
            break;
        }
    }

    int string_length = email.length();
    if(string_length >= 7){ //check for minimum length of email
        int last_index = string_length - 4; //acount for .com or .net etc
        std::string domain = email.substr(last_index, 4); //get 4 letter substring from given index

        std::cout <<domain << std::endl;
        if(domain == ".com" || domain == ".net" || domain == ".org"){ //if this domain
            contains_valid_dot = true;
        }
    }

    if(contains_valid_dot == true && contain_at_symbol == true){
        is_valid_email = true;
    }

    return is_valid_email;
}

/*function that takes inputs from user to create a new account. takes an argument of a reference to a session object
Return a vector of strings if email is valid and password meets complexity and no account with username exists*/
std::vector<std::string> create_new_account(Session& session){
    std::vector<std::string> account_details;
    bool meets_input_requirements = false;
    while(!meets_input_requirements){ //get account information from user while requiremnets arent met
        std::string new_user, passcode, new_email;
        bool password_req = false;
        bool email_req = false;
        bool username_is_unique = false;
        bool is_an_email = false;
        std::shared_ptr<sql::ResultSet> check_user;

        std::cout << "Username: ";
        new_user = take_string_input(); // check username now in DB
        check_user = get_username(new_user, session.getConnection());

        std::cout << "Password: ";
        passcode = take_string_input(); //get inputted password
        password_req = check_password_complexity(passcode); //check for pw complexity

        std::cout << "Email: ";
        new_email = take_string_input();
        email_req = check_valid_email(new_email);//check contains @ symbol and ends with .com/.net/.org/.gov

        if(password_req == true && email_req == true && !check_user->next()){ //check bools true and ther are no rows (didnt return a user)
            meets_input_requirements = true;
            account_details.push_back(new_user);
            account_details.push_back(passcode);
            account_details.push_back(new_email);
            break;
        }
    }

    return account_details;
}

int main(){
    std::srand(std::time(0)); // seed random 
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
            case(1): {//create account
                std::cout << "Creating an account.. " << std::endl; 
                bool meets_input_requirements = false;
                std::vector<std::string> account_details = create_new_account(session); //call function to get a vector of strings containing inputs

                User new_user_account = User(account_details[0], account_details[1], account_details[2]); //create user object using account details

                break; 
            }
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