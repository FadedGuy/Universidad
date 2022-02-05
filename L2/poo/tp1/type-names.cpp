#include <cstdio>
#include <typeinfo>

int main(){
    printf("bool: \"%s\"\n", typeid(bool).name());
    printf("char: \"%s\"\n", typeid(char).name());
    printf("signed char: \"%s\"\n", typeid(signed char).name());
    printf("unsigned char: \"%s\"\n", typeid(unsigned char).name());
    printf("wchar_t: \"%s\"\n", typeid(wchar_t).name());
    printf("short: \"%s\"\n", typeid(short).name());
    printf("unsigned short: \"%s\"\n", typeid(unsigned short).name());
    printf("int: \"%s\"\n", typeid(int).name());
    printf("unsigned int: \"%s\"\n", typeid(unsigned int).name());
    printf("long: \"%s\"\n", typeid(long).name());
    printf("unsigned long: \"%s\"\n", typeid(unsigned long).name());
    printf("float: \"%s\"\n", typeid(float).name());
    printf("double: \"%s\"\n", typeid(double).name());
    printf("long double: \"%s\"\n", typeid(long double).name());    
    printf("bool*: \"%s\"\n", typeid(bool*).name());
    printf("char*: \"%s\"\n", typeid(char*).name());
    printf("signed char*: \"%s\"\n", typeid(signed char*).name());
    printf("unsigned char*: \"%s\"\n", typeid(unsigned char*).name());
    printf("wchar_t*: \"%s\"\n", typeid(wchar_t*).name());
    printf("short*: \"%s\"\n", typeid(short*).name());
    printf("unsigned short*: \"%s\"\n", typeid(unsigned short*).name());
    printf("int*: \"%s\"\n", typeid(int*).name());
    printf("unsigned int*: \"%s\"\n", typeid(unsigned int*).name());
    printf("long*: \"%s\"\n", typeid(long*).name());
    printf("unsigned long*: \"%s\"\n", typeid(unsigned long*).name());
    printf("float*: \"%s\"\n", typeid(float*).name());
    printf("double*: \"%s\"\n", typeid(double*).name());
    printf("long double*: \"%s\"\n", typeid(long double*).name());

    return 0;
}