#include <stdio.h>
#include <limits.h>

int main()
{
    /*4 byte max*/
    unsigned long max; 
    unsigned long i;

    do
    {
        printf("max: ");
        scanf("%lu", &max);
        while(getchar() != '\n');
    }while(!(max >= 0 && max < UINT_MAX));
    
    for(i = 0; i <= max; i++)
    {
        printf("%lu\n", i);
    }

    return 0;
}