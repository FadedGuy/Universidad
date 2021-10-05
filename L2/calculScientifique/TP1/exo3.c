#include <stdio.h>
#include "interpolation.h"

int main()
{
    int nbElements;
    FILE *pFile;

    pFile = fopen("exo3.dat", "r+");
    fscanf(pFile, "%d", &nbElements);

    double X[nbElements];
    double Y[nbElements];

    printf("%d points\n", nbElements);
    for(int i = 0; i < nbElements; i++)
    {
        fscanf(pFile, "%lg", &X[i]);
        fscanf(pFile, "%lg", &Y[i]);

        //printf("%d %f\n", X[i], Y[i]);
    }

    double N[nbElements*2];
    differences_divises(N, X, Y, nbElements);
    for(int i = 0; i < nbElements; i++)
    {
        printf("%lg %lg\n", N[i], N[i+nbElements]);
    }

    return 0;
}