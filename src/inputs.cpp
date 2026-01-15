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

        std::cout <<domain << "\n";
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
std::vector<std::string> take_input_for_new_account(){
    std::vector<std::string> account_details;
    bool meets_input_requirements = false;
    while(!meets_input_requirements){ //get account information from user while requiremnets arent met
        std::string new_user, passcode, new_email;
        bool password_req = false;
        bool email_req = false;
        bool is_an_email = false;

        std::cout << "Username: ";
        new_user = take_string_input();

        std::cout << "Password: ";
        passcode = take_string_input(); //get inputted password
        password_req = check_password_complexity(passcode); //check for pw complexity

        std::cout << "Email: ";
        new_email = take_string_input();
        email_req = check_valid_email(new_email);//check contains @ symbol and ends with .com/.net/.org/.gov

        if(password_req == true && email_req == true){ //check bools true and ther are no rows (didnt return a user)
            account_details.push_back(new_user);
            account_details.push_back(passcode);
            account_details.push_back(new_email);
            meets_input_requirements = true;
            break;
        }
        else{
            std::cout << "\n\n\t\tSomething didnt pass my account sniffer";
        }
    }

    return account_details;
}