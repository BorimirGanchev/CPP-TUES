#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

/**
 * Your task is to add a counter of how many Objects of type String are currently in the memory, and how many have been created.
 */

class String
{
    static int currentObjects;
    static int createdObjects;
    char *data;
    size_t length;

public:
    String(const char *data)
    {
        this->length = strlen(data);
        this->data = strdup(data);
        createdObjects++;
        currentObjects++;
    }

    String(const String &other)
    {
        this->length = other.length;
        this->data = strdup(other.data);
        createdObjects++;
        currentObjects++;
    }

    String &operator=(const String &other)
    {
        if (this != &other)
        {
            free(this->data);
            this->length = other.length;
            this->data = strdup(other.data);
        }
        return *this;
    }

    ~String()
    {
        free(this->data);
        currentObjects--;
    }

    const char *getCString() const
    {
        return this->data;
    }

    size_t strlength() const
    {
        return this->length;
    }

    static int getCurrentStringCount() {
        return currentObjects;
    }

    static int getTotalStringCount(){
        return createdObjects;
    }
};

int String::createdObjects = 0;
int String::currentObjects = 0;

int main()
{
    String *s = new String("Test message");

    vector<String *> arr;
    for (int i = 0; i < 3; i++)
    {
        arr.push_back(new String("Test message"));
    }

    cout << "Expected: 4, got: " << String::getCurrentStringCount() << endl;
    delete s;
    cout << "Expected: 3, got: " << String::getCurrentStringCount() << endl;
    cout << "Expected: 4, got: " << String::getTotalStringCount() << endl;

    return 0;
}