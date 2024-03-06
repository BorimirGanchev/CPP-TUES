#include <iostream>
#include <cstring> 

using namespace std;

class String
{
    char *data;
    size_t length;

public:
    String(const char *data) {
        length = strlen(data);
        this->data = new char[length + 1];
        strcpy(this->data, data);
    }

    String(const String &other) {
        length = other.length;
        data = new char[length + 1];
        strcpy(data, other.data);
    }   

    void printData() {
        std::cout << "Data: " << this->data << std::endl;
        std::cout << "Data: " << data << std::endl;
    }

    String &operator=(const String &other) {
        if (this != &other) {
            delete[] data;
            length = other.length;
            data = new char[length + 1];
            strcpy(data, other.data);
        }
        return *this;
    }

    ~String() {
        delete[] data;
    }

    const char *getCString() const {
        return data;
    }

    size_t strlength() const {
        return length;
    }
};

int main() {
    String myString("Test message");

    cout << "Expected: Test message, got: " << myString.getCString() << endl;

    String stringFromCopyConstructor(myString);
    cout << "Expected: Test message, got: " << stringFromCopyConstructor.getCString() << endl;

    String string("Test message 2");

    string = myString;
    cout << "Expected: Test message, got: " << string.getCString() << endl;

    myString.printData();

    return 0;
}
