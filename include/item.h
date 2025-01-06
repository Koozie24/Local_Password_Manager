#include <string>

class Item{ //takes 4 string arguments then creates creates a credential item object, encrypts password string and writes it to database 
    private:
        std::string type;
        std::string title;
        std::string username;
        std::string password;
    public:
        const std::string& getType() const {return type; }
        const std::string& getTitle() const {return title; }
        const std::string& getUsername() const {return username; }
        const std::string& getPassword() const {return password; }

        Item(std::string type, std::string title, std::string username, std::string password)
            : type(std::move(type)), title(std::move(title)), username(std::move(username)), password(std::move(password)){
                //encryption functions
                //function for adding to database
                //function to display successful creation and saving
            }
};