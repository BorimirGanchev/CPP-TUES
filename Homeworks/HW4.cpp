#include <iostream>
#include <exception>
#include <cstring>


using namespace std;

/**
 * Your task is to create a class MyException that inherits from std::exception and overrides the what() method.
 * You have the signature of the what method below.
 *
 * I want you to create:
 *  - Default constructor that will have a default message: MyCustomError: No message!
 *  - Constructor with a message
 *  - Destructor
 *  - Copy constructor
 *  - Copy assignment operator
 *  - what() method that will print the message in the following format: MyCustomError: <message>
 */

class MyException : public std::exception
{
    char *message;
public:
    const char *what() const noexcept{
        const char* prefix = "MyCustomError: ";
        char* newMessage = new char[strlen(prefix) + strlen(message) + 1];
        strcpy(newMessage, prefix);
        strcat(newMessage, message);
        return newMessage;
    }

    MyException(){
        message = strdup("No message!");
    }

    MyException(const char *message){
        this->message = strdup(message);
    }

    ~MyException(){
        delete[] message;
    }

    MyException(MyException &other){
        if (other.message != nullptr){
            this->message = strdup(other.message);
        }
    }

    MyException &operator=(MyException &other){
        if (this != &other && other.message != nullptr){
            delete[] this->message;
            this->message = strdup(other.message);
        }
        return *this;
    }
};

int main()
{
    MyException e1;
    cout << "Expected: MyCustomError: No message!"
        << "Got: " << e1.what() << endl;

    MyException e2("This is a message");
    cout << "Expected: MyCustomError: This is a message"
        << "Got: " << e2.what() << endl;
    return 0;   
}