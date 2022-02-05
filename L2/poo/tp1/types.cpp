#include <cstdio>
#include <cfloat>
#include <climits>
#include <cwchar>

int main(){
    printf("bool: %ld byte(s), %d to %d\n", sizeof(bool), false, true);
    printf("char: %ld byte(s), %d to %d\n", sizeof(char), CHAR_MIN, CHAR_MAX);
    printf("signed char: %ld byte(s), %d to %d\n", sizeof(signed char), SCHAR_MIN, SCHAR_MAX);
    printf("unsigned char: %ld byte(s), %d to %d\n", sizeof(unsigned char), 0, UCHAR_MAX);
    printf("wchar_t: %ld byte(s), %d to %d\n", sizeof(wchar_t), WCHAR_MIN, WCHAR_MAX);
    printf("short: %ld byte(s), %d to %d\n", sizeof(short), SHRT_MIN, SHRT_MAX);
    printf("unsigned short: %ld byte(s), %d to %d\n", sizeof(unsigned short), 0, USHRT_MAX);
    printf("int: %ld byte(s), %d to %d\n", sizeof(int), INT_MIN, INT_MAX);
    printf("unsigned int: %ld byte(s), %d to %d\n", sizeof(unsigned int), 0, UINT_MAX);
    printf("long: %ld byte(s), %ld to %ld\n", sizeof(long), LONG_MIN, LONG_MAX);
    printf("unsigned long: %ld byte(s), %d to %ld\n", sizeof(unsigned long), 0, ULONG_MAX);
    printf("float: %ld byte(s), %f to %f\n", sizeof(float), FLT_MIN, FLT_MAX);
    printf("double: %ld byte(s), %f to %f\n", sizeof(double), DBL_MIN, DBL_MAX);
    printf("long double: %ld byte(s), %Lf to %Lf\n", sizeof(long double), LDBL_MIN, LDBL_MAX);

    return 0;
}