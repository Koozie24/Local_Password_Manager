#ifndef DISPLAY_H

#define DISPLAY_H

#include <string>
#include <iostream>
#include "inputs.h"

/*Clears the screen on Windows and Linux OS's*/
void clear_screen();

/*Prints options at start of program*/
void display_start_screen();

/*Prints options at home screen*/
void display_home_screen(const std::string &signed_in_user_name);

std::pair <std::string, std::string> display_sign_in_screen();

#endif