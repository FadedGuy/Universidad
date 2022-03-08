#include <iostream>
#include <typeinfo>

int main(){
    std::cout << "bool: \"" << typeid(bool).name() << "\"\n";
    std::cout << "char: \"" << typeid(char).name() << "\"\n";
    std::cout << "signed char: \"" << typeid(signed char).name() << "\"\n";
    std::cout << "unsigned char: \"" << typeid(unsigned char).name() << "\"\n";
    std::cout << "wchar_t: \"" << typeid(wchar_t).name() << "\"\n";
    std::cout << "short: \"" << typeid(short).name() << "\"\n";
    std::cout << "unsigned short: \"" << typeid(unsigned short).name() << "\"\n";
    std::cout << "int: \"" << typeid(int).name() << "\"\n";
    std::cout << "unsigned int: \"" << typeid(unsigned int).name() << "\"\n";
    std::cout << "float: \"" << typeid(float).name() << "\"\n";
    std::cout << "double: \"" << typeid(double).name() << "\"\n";
    std::cout << "long double: \"" << typeid(long double).name() << "\"\n";
    std::cout << "bool*: \"" << typeid(bool*).name() << "\"\n";
    std::cout << "char*: \"" << typeid(char*).name() << "\"\n";
    std::cout << "signed char*: \"" << typeid(signed char*).name() << "\"\n";
    std::cout << "unsigned char*: \"" << typeid(unsigned char*).name() << "\"\n";
    std::cout << "wchar_t*: \"" << typeid(wchar_t*).name() << "\"\n";
    std::cout << "short*: \"" << typeid(short*).name() << "\"\n";
    std::cout << "unsigned short*: \"" << typeid(unsigned short*).name() << "\"\n";
    std::cout << "int*: \"" << typeid(int*).name() << "\"\n";
    std::cout << "unsigned int*: \"" << typeid(unsigned int*).name() << "\"\n";
    std::cout << "float*: \"" << typeid(float*).name() << "\"\n";
    std::cout << "double*: \"" << typeid(double*).name() << "\"\n";
    std::cout << "long double*: \"" << typeid(long double*).name() << "\"\n";
    
    return 0;
}