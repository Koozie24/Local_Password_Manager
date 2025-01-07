#include <string>
#include <iostream>

/*Prints options at start of program*/
void display_sign_in_screen(){
    std::cout << "Passmate: Your simple password manager" << std::endl;
    std::cout << "  (1) Create an account" << std::endl;
    std::cout << "  (2) Sign-in to an existing account" << std::endl;
    std::cout << "  (3) Testing pass on" << std::endl;
    std::cout << "  Input number: ";
}
/*Prints options at home screen*/
void display_home_screen(){
    std::cout << "Passmate: Your simple password manager" << std::endl;
    std::cout << "  (1) Look-Up a Credential" << std::endl;
    std::cout << "  (2) Add a new credential item" << std::endl;
    std::cout << "  (3) Browse credentials" << std::endl;
    std::cout << "  (4) Sign-out of current session" << std::endl;
    std::cout << "  Input number: ";
}