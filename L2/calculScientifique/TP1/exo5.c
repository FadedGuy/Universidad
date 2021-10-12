#include <stdio.h>
#include "interpolation.h"

int main()
{
    int nbElements;
    FILE *pFile;

    pFile = fopen("exo4.dat", "r+");
    fscanf(pFile, "%d", &nbElements);

    double X[nbElements];
    double Y[nbElements];

    for(int i = 0; i < nbElements; i++)
    {
        fscanf(pFile, "%lg", &X[i]);
        fscanf(pFile, "%lg", &Y[i]);

    }
    // printf("%lg\n", par_morceaux(2016.5, X, Y, nbElements));


    // double N[nbElements];
    // differences_divises(N, X, Y, nbElements);
    // printf("Exo4 %lg \tExo5 %lg\n", eval_p_dd(2016.5, N, X, nbElements), par_morceaux(2016.5, X, Y, nbElements));

    for(int k = 0; k <= 1000; k++)
    {
        double zk = 2007 + ((10*(double)k) / 1000);
        printf("%lg %lg\n", zk, par_morceaux(zk, X, Y, nbElements));
    }
    return 0;
}