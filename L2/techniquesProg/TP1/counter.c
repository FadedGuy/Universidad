#include <stdio.h>
#include <limits.h>

int main()
{
    /*4 byte max*/
    unsigned long max; 
    unsigned long i;

    do
    {
        scanf("%lu", &max);
        while(getchar() != '\n');
        printf("%lu\n", max);
    }while(max < 0);
    
    for(i = 0; i <= max; i++)
    {
        printf("%lu\n", i);
    }

    return 0;
}