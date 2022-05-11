/**
* \file str2i-error.h
*/
#ifndef STR2I_ERROR_H
#define STR2I_ERROR_H
#include <string> // for string
using namespace std; // for string
/**
* A string to int conversion exception.
*/
class str2i_error: public exception
{
    string str; /**< The string describing this string to int conversion exception. */
    public:
        /**
        * Constructs a new string to int conversion exception.
        * \param str The string that cannot be converted to an int.
        */
        str2i_error(string str);
        /**
        * Destroys an existing string to int conversion exception.
        */
        ~str2i_error() throw ();
        /**
        * Creates a string describing this string to int conversion exception.
        * This string is "str2i_error: unable to convert the string \"str\" to an int".
        * \return The string describing this string to int conversion exception.
        */
        const char *what() const throw ();
};
#endif