#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void quadratic_equation(double a, double b, double c, int* nsol, double* sol1, double* sol2)
{
    double discriminant = ((b*b) - (4*a*c));
    if(discriminant < 0)
    {
        *nsol = 0;
    }
    else if(discriminant == 0)
    {
        *nsol = 1;
        *sol1 = ((-b) / (2*a));
    }
    else
    {
        *nsol = 2;
        *sol1 = ((-b - sqrt(discriminant)) / 2*a);
        *sol2 = ((-b + sqrt(discriminant)) / 2*a);
    }
}

int main(int argc, char* argv[])
{
    int nsol = 0;
    double a, b, c, sol1, sol2;
    char* pEnd;

    if(argc != 4)
    {
        fprintf(stderr, "invalid number of arguments\n");
        return 1;
    }

    a = strtod(argv[1], &pEnd);
    b = strtod(argv[2], &pEnd);
    c = strtod(argv[3], NULL);

    if(a == 0 || b == 0 || c == 0)
    {
        if(a == 0)
        {
            fprintf(stderr, "invalid number for the first argument\n");
            return 1;
        }
        else if(b == 0)
        {
            fprintf(stderr, "invalid number for the second argument\n");
            return 1;
        }
        else
        {
            fprintf(stderr, "invalid number for the third argument\n");
            return 1;
        }
    }

    quadratic_equation(a, b, c, &nsol, &sol1, &sol2);
    if(nsol == 0)
    {
        printf("%d solutions\n", nsol);
    }
    else if(nsol == 1)
    {
        printf("%d solution: %f\n", nsol, sol1);
    }
    else
    {
        printf("%d solutions: %f and %f\n", nsol, sol1, sol2);
    }

    return 0;
}