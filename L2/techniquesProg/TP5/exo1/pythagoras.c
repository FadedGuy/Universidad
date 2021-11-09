#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double pythagoras(double a, double b)
{
    return (sqrt((a*a) + (b*b)));
}

int main(int argc, char* argv[])
{
    double a, b;
    char* pEnd;
    if(argc != 3)
    {
        fprintf(stderr, "invalid number of arguments\n");
        return 1;
    }

    a = strtod(argv[1], &pEnd);
    b = strtod(argv[2], NULL);

    if(a == 0 || b == 0)
    {
        if(a == 0)
        {
            fprintf(stderr, "invalid number for the first argument\n");
            return 1;
        }
        else
        {
            fprintf(stderr, "invalid number for the second argument\n");
            return 1;
        }
    }

    printf("hypotenuse: %f\n", pythagoras(a, b));

    return 0;
}