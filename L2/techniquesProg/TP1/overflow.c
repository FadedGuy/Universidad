#include <stdio.h>

int main()
{
    /*
        error: overflow in conversion from ‘int’ to ‘short int’ 
        changes value from ‘32768’ to ‘-32768’ [-Werror=overflow]
    */
    short entier = 32767;
    /* On peut noter dans le print qu'il overflow */
    printf("%d\n", ++entier); 
    return 0;
}