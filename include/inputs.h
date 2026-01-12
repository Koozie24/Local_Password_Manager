#ifndef INPUTS_H

#define INPUTS_H
#include <string>
#include <iostream>
#include <limits>

std::string take_string_input();

/*Takes input from user until valid integer is recieved. Returns an int*/
int take_single_int_input(int number_of_options);

bool check_password_complexity(const std::string& password);

bool check_valid_email(const std::string& email);

#endif