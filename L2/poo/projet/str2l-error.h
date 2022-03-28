/**
* \file str2l-error.h
*/
#ifndef STR2L_ERROR_H
#define STR2L_ERROR_H
#include <string> // for string
using namespace std; // for string
/**
* A string to long conversion exception.
*/
class str2l_error: public exception
{
    string str; /**< The string describing this string to long conversion exception. */
    public:
        /**
        * Constructs a new string to long conversion exception.
        * \param str The string that cannot be converted to a long.
        */
        str2l_error(string str);
        /**
        * Destroys an existing string to long conversion exception.
        */
        ~str2l_error() throw ();
        /**
        * Creates a string describing this string to long conversion exception.
        * This string is "str2l_error: unable to convert the string \"str\" to a long".
        * \return The string describing this string to long conversion exception.
        */
        const char *what() const throw ();
};
#endif
