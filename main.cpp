#include <iostream>
#include <algorithm>
#include <string>
#include <limits>
#include "include/item.h"
#include "include/user.h"

/*Prints options at start of program*/
void display_sign_in_screen(){
    std::cout << "Passmate: Your simple password manager" << std::endl;
    std::cout << "  (1) Create an account" << std::endl;
    std::cout << "  (2) Sign-in to an existing account" << std::endl;
    std::cout << "  (3) Testing pass on" << std::endl;
    std::cout << "  Input number: ";
}

/*Takes input from user until valid integer is recieved. Returns an int*/
int take_single_int_input(){
    int single_input;
    for(;;){
        std::cin >> single_input;
        if(single_input == 1 || single_input == 2 || single_input == 3){
            break;
        }
        std::cout << "Sorry, that option is not valid. Try again from the options listed: ";
        std::cin.clear(); //reset cin state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //clear input buffer of invalid input
    }

    return single_input;
}


void display_home_screen(){
    std::cout << "Passmate: Your simple password manager" << std::endl;
    std::cout << "  (1) Look-Up a Credential" << std::endl;
    std::cout << "  (2) Add a new credential item" << std::endl;
    std::cout << "  (3) Update an existing credential item" << std::endl;
    std::cout << "  Input number: ";
}

int main(){
    
    display_sign_in_screen(); //show sign in/create account options
    int sign_in_screen_command = take_single_int_input(); //take user command

    switch(sign_in_screen_command)
    {
        case(1): //create account
        case(2): //account sign in
        case(3): //testing  advance to home screen
            display_home_screen();


            break;
    }

    return 0;
}