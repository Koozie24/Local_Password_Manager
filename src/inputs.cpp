#include <string>
#include <iostream>
#include <limits>
#include "../include/inputs.h"

std::string take_string_input(){
    for(;;){
        std::string user_input;
        getline(std::cin, user_input);

        return user_input;
    }
}

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