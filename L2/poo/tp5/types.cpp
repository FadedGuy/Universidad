#include <iostream>
#include <cfloat>
#include <climits>
#include <cwchar>

int main(){
    std::cout << "bool: " << sizeof(bool) << " byte(s), " << false << " to " << true << "\n";
    std::cout << "char: " << sizeof(char) << " byte(s), " << CHAR_MIN << " to " << CHAR_MAX << "\n";
    std::cout << "signed char: " << sizeof(signed char) << " byte(s), " << SCHAR_MIN << " to " << SCHAR_MAX << "\n";
    std::cout << "unsigned char: " << sizeof(unsigned char) << " byte(s), " << 0 << " to " << UCHAR_MAX << "\n";
    std::cout << "wchar_t: " << sizeof(wchar_t) << " byte(s), " << WCHAR_MIN << " to " << WCHAR_MAX << "\n";
    std::cout << "short: " << sizeof(short) << " byte(s), " << SHRT_MIN << " to " << SHRT_MAX << "\n";
    std::cout << "unsigned short: " << sizeof(unsigned short) << " byte(s), " << 0 << " to " << USHRT_MAX << "\n";
    std::cout << "int: " << sizeof(int) << " byte(s), " << INT_MIN << " to " << INT_MAX << "\n";
    std::cout << "unsigned int: " << sizeof(unsigned int) << " byte(s), " << 0 << " to " << UINT_MAX << "\n";
    std::cout << "long: " << sizeof(long) << " byte(s), " << LONG_MIN << " to " << LONG_MAX << "\n";
    std::cout << "unsigned long: " << sizeof(unsigned long) << " byte(s), " << 0 << " to " << ULONG_MAX << "\n";
    std::cout << "float: " << sizeof(float) << " byte(s), " << FLT_MIN << " to " << FLT_MAX << "\n";
    std::cout << "double: " << sizeof(double) << " byte(s), " << DBL_MIN << " to " << DBL_MAX << "\n";
    std::cout << "long double: " << sizeof(long double) << " byte(s), " << LDBL_MIN << " to " << LDBL_MAX << "\n";

    return 0;
}