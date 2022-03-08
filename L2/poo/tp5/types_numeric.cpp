#include <iostream>
#include <cfloat>
#include <climits>
#include <cwchar>
#include <limits>

int main(){
    std::cout << "bool: " << sizeof(bool) << " byte(s), " << false << " to " << true << "\n";
    std::cout << "char: " << sizeof(char) << " byte(s), " << std::numeric_limits<char>::min() << " to " << std::numeric_limits<char>::max() << "\n";
    std::cout << "signed char: " << sizeof(signed char) << std::numeric_limits<signed char>::min() << " to " << std::numeric_limits<signed char>::max() << "\n";
    std::cout << "unsigned char: " << sizeof(unsigned char) << std::numeric_limits<unsigned char>::min() << " to " << std::numeric_limits<unsigned char>::max() << "\n";
    std::cout << "wchar_t: " << sizeof(wchar_t) << " byte(s), " << std::numeric_limits<wchar_t>::min() << " to " << std::numeric_limits<wchar_t>::max() << "\n";
    std::cout << "short: " << sizeof(short) << " byte(s), " << std::numeric_limits<short>::min() << " to " << std::numeric_limits<short>::max() << "\n";
    std::cout << "unsigned short: " << sizeof(unsigned short) << std::numeric_limits<unsigned short>::min() << " to " << std::numeric_limits<unsigned short>::max() << "\n";
    std::cout << "int: " << sizeof(int) << " byte(s), " << std::numeric_limits<int>::min() << " to " << std::numeric_limits<int>::max() << "\n";
    std::cout << "unsigned int: " << sizeof(unsigned int) << " byte(s), " << std::numeric_limits<unsigned int>::min() << " to " << std::numeric_limits<unsigned int>::max() << "\n";
    std::cout << "long: " << sizeof(long) << " byte(s), " << std::numeric_limits<long>::min() << " to " << std::numeric_limits<long>::max() << "\n";
    std::cout << "unsigned long: " << sizeof(unsigned long) << " byte(s), " << std::numeric_limits<unsigned long>::min() << " to " << std::numeric_limits<unsigned long>::max() << "\n";
    std::cout << "float: " << sizeof(float) << " byte(s), " << std::numeric_limits<float>::min() << " to " << std::numeric_limits<float>::max() << "\n";
    std::cout << "double: " << sizeof(double) << " byte(s), " << std::numeric_limits<double>::min() << " to " << std::numeric_limits<double>::max() << "\n";
    std::cout << "long double: " << sizeof(long double) << " byte(s), " << std::numeric_limits<long double>::min() << " to " << std::numeric_limits<long double>::max() << "\n";

    return 0;
}