#include <stdio.h>
#include <limits.h>
#include <float.h>

int main()
{
    printf("char: %ld byte(s), %d to %d\n", sizeof(char), CHAR_MIN, CHAR_MAX);
    printf("signed char: %ld byte(s), %d to %d\n", sizeof(char), SCHAR_MIN, SCHAR_MAX);
    printf("unsigned char: %ld byte(s), %d to %d\n", sizeof(unsigned char), 0, UCHAR_MAX);
    printf("short: %ld byte(s), %d to %d\n", sizeof(short), SHRT_MIN, SHRT_MAX);
    printf("unsigned short: %ld byte(s), %d to %d\n", sizeof(unsigned short), 0, USHRT_MAX);
    printf("int: %ld byte(s), %d to %d\n", sizeof(int), INT_MIN, INT_MAX);
    printf("unsigned int: %ld byte(s), %d to %d\n", sizeof(unsigned int), 0, UINT_MAX); /*UINT_MAX -1*/
    printf("long: %ld byte(s), %ld to %ld\n", sizeof(long), LONG_MIN, LONG_MAX);
    printf("unsigned long: %ld byte(s), %d to %ld\n", sizeof(unsigned long), 0, ULONG_MAX); /*ULONG_MAX -1*/
    printf("float: %ld byte(s), %f to %f\n", sizeof(float), FLT_MIN, FLT_MAX); /*FLT_MIN 0*/
    printf("double: %ld byte(s), %g to %g\n", sizeof(double), DBL_MIN, DBL_MAX);
    printf("long double: %ld byte(s), %Lg to %Lg\n", sizeof(long double), LDBL_MIN, LDBL_MAX);

    return 0;
}