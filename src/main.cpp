#include <iostream>
#include <algorithm>
#include <ctime>
#include "../include/item.h"
#include "../include/user.h"
#include "../include/display.h"
#include "../include/session.h"
#include "../include/inputs.h"
#include "../include/db_operations.h"


int main(){
    std::srand(std::time(0)); // seed random 
    bool running = true;

    Creds credentials;
    const std::string file_path = "info.txt";
    read_in_creds(file_path, credentials);

    while(running){
        Session * session = new Session("tcp://127.0.0.1:3306", credentials.account, credentials.password, "PASSMATE"); //initialize session with localhost,
        User * logged_in_user = nullptr; // declate user in scope of main
        std::string signed_in_user_name;
        bool current_session = false;

        //show sign in/create account options
        clear_screen();
        display_start_screen(); 

        int start_screen_command = take_single_int_input(3); //take a command from the user
        std::unique_ptr<sql::ResultSet> result_user;

        /*-
        ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        -----------------Switch case to handle home screen create account / sign in-------------------------------------------------------------------------------------------------------------------------------------
        ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        */

        switch(start_screen_command){
            case(1): //create account
            {
                while(1){ //loop until account is created
                    std::cout << "Creating an account.. " << "\n"; 
                    std::vector<std::string> account_details = take_input_for_new_account(); //call function to get a vector of strings containing inputs

                    Account new_user_account = Account(account_details[0], account_details[1], account_details[2], session->getConnection()); //create user object using account details

                    if(new_user_account.getAccountCreatedStatus()) break; //break out of loop
                }
                break;
            }
            case(2): //account sign in
            {  
                int first_acct_inp = 0;
                bool account_name_valid = false;
                
                Authentication * login_user = nullptr;

                while(!account_name_valid){ //attempt to input a valid account name
                    if(first_acct_inp > 0 ) std::cout << "\nThere was no account found matching that name.";
                    std::string acct_name_input = take_login_attempt_name();
                    login_user = new Authentication(acct_name_input, session->getConnection());

                    if(login_user->getUserExists()){
                        account_name_valid = true;
                        break;
                    }
                    if(first_acct_inp == 0) first_acct_inp++;

                    delete login_user;
                }

                if(!login_user->checkClearToAttemptAuth()) {std::cout << "\n\n\t\t Something wrong, clear to attempt auth failed"; break;}
                
                bool first_attempt = true;
                while(login_user->getAttemptsRemaining() > 0){

                    clear_screen();
                    if(login_user->getAttemptsRemaining() < 3) std::cout << "\n You have " << login_user->getAttemptsRemaining() << " login attempts remaining.";

                    std::string acct_password_input = take_login_attempt_password();


                    //login_success = login_user.getAuthStatus();
    
                }
                /*
                while(!current_session){
                    clear_screen();
                    if(attempted_sign_in) std::cout << "Username or password is incorrect..." << "\n", std::cout << "You have "<< (max_attempts_allowed - sign_in_attempts) << " attemps remaining. " << "\n";

                    if(sign_in_attempts == max_attempts_allowed) std::cout << "Too many failed attempts." << "\n", exit(1);

                    std::pair<std::string, std::string> login_string = display_sign_in_screen(); //show screen to input username
    
                    result_user = get_username(login_string.first, session->getConnection()); //get resulting user account info

                    if(result_user && result_user->next()){ //check not nullptr and result user returned something
                        if((login_string.first == result_user->getString("username"))
                         && (login_string.second == result_user->getString("password_hash"))){ //compare input to stored username and pass hash
                            signed_in_user_name = login_string.first;
                            current_session = true; //signed in is true
                        }
                    }
                    else{
                        attempted_sign_in = true;
                        sign_in_attempts++;
                    }
                }
                */
                delete login_user;
                break;
            }
            case(3): //exit program
                running = false;
                delete logged_in_user;
                break;
        }

          /*-
        ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        -----------------Switch case to handle authenticated user functions --------------------------------------------------------------------------------------------------------------------------------------------
        ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        */

        /*
        while(current_session){ //while current user is signed in
            clear_screen();
            display_home_screen(signed_in_user_name);
                int home_screen_command = take_single_int_input(4);

                switch (home_screen_command){
                    case(1):
                        std::cout << "Looking up a credential.. " << "\n"; 
                        break;
                    case(2):
                        std::cout << "Adding a new credential.. " << "\n"; 
                        break;
                    case(3):
                        std::cout << "Browse existing Credentials.. " << "\n"; 
                        break;
                    case(4):
                        std::cout << "Sign-out of current session..." << "\n";
                        current_session = false;
                        std::cout << "Exiting... " << "\n";
                        break;
                }
        } */
    }
    return 0;
}

