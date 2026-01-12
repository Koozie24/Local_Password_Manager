#include <string>
#include <iostream>
#include "../include/display.h"

/*Clears the screen on Windows and Linux OS's*/
void clear_screen(){
    #ifdef WINDOWS
        std::system("cls");
    #else
        std::system("clear");
    #endif
}

/*Prints options at start of program*/
void display_start_screen(){
    std::cout << "Passmate: Your simple password manager" << std::endl;
    std::cout << "  (1) Create an account" << std::endl;
    std::cout << "  (2) Sign-in to an existing account" << std::endl;
    std::cout << "  (3) Exit program" << std::endl;
    std::cout << "  Input number: ";
}
/*Prints options at home screen*/
void display_home_screen(const std::string &signed_in_user_name){
    std::cout << "Passmate: Your simple password manager - Welcome " << signed_in_user_name << std::endl;
    std::cout << "  (1) Look-Up a Credential" << std::endl;
    std::cout << "  (2) Add a new credential item" << std::endl;
    std::cout << "  (3) Browse credentials" << std::endl;
    std::cout << "  (4) Sign-out of current session" << std::endl;
    std::cout << "  Input number: ";
}

std::pair <std::string, std::string> display_sign_in_screen(){
    std::pair<std::string, std::string> login_string;
    std::cout << "Sign-in to your Passmate account" << std::endl;
    std::cout << "Enter your username: ";
    login_string.first = take_string_input(); //get password input

    std::cout << "Enter your password: " ;
    login_string.second = take_string_input(); //get password input
    
    return login_string;
}
