#include <iostream>

using namespace std;

////////////////////////////////////////////////////////////////
// Types
// int, unsigned int, long, short, long long
// float, double
// char, string
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
// cin
// cout
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
// Dynamic memory
// malloc, calloc, realloc, free
// new, delete
////////////////////////////////////////////////////////////////


//Here we allocate a memmory with the function malloc.
//Where size_t get the exact number of integers
char *Malloc(size_t size)
{
    char *arr = new char[size];

    return arr;
}

/*
const char* the_string : I can change which char the_string points to, but I cannot modify the char to which it points.

char* const the_string : I cannot change which char the_string points to, but I can modify the char to which it points.

const char* const the_string : I cannot change which char the_string points to, nor can I modify the char to which it points.*/

char *Realloc(const char *const src, size_t size)
{
    // used to allocate memory dynamically for a variable or an object at runtime.

    char *arr = new char[size];
    for (size_t i = 0; i < size; i++)
    {
        arr[i] = src[i];
    }

    //delete is an operator that is used to destroy array and non-array(pointer) objects which are dynamically created by the new operator.

    delete[] src;
    return arr;
}

int main()
{
    // char arr[10];
    int a, b;
    cin >> a >> b;

    cout << "The number you chose is: " << a << endl;
}