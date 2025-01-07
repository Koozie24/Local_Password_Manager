#include <iostream>
#include <algorithm>
#include <string>
#include <limits>
#include "include/item.h"
#include "include/user.h"
#include "include/display.h"
#include "include/session.h"

/*Takes input from user until valid integer is recieved. Returns an int*/
int take_single_int_input(int number_of_options){
    int single_input;
    for(;;){
        std::cin >> single_input;
        if(number_of_options == 3){ //for sign in with 3 choices
            if(single_input >= 1 && single_input <= 3){
                break;
            }
        }
        if(number_of_options == 4){ //for home page with 4 choices
            if(single_input >=1 && single_input <= 4){
                break;
            }
        }
        std::cout << "Sorry, that option is not valid. Try again from the options listed: ";
        std::cin.clear(); //reset cin state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //clear input buffer of invalid input
    }

    return single_input;
}

int main(){
    
    Session session("tcp://127.0.0.1:3306", "passmateadmin", "D1774%!f71pG", "passmate"); //initialize session
    
    bool current_session = false;
    display_sign_in_screen(); //show sign in/create account options
    int sign_in_screen_command = take_single_int_input(3); //take user command

    switch(sign_in_screen_command){ //handling sign in screen
        case(1): //create account
            std::cout << "Creating an account.. " << std::endl; 
            break; 
        case(2): //account sign in
            std::cout << "Signing into an account.. " << std::endl; 
            current_session = true;
            break;
        case(3): //testing  advance to home screen will change to exit program
            current_session = true;
            break;
    }

    while(current_session){ //while current user is signed in
        display_home_screen();
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

    return 0;
}