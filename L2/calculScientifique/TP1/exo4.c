#include "interpolation.h"
#include <stdio.h>

int main()
{
    int nbElements;
    FILE *pFile;

    pFile = fopen("exo4.dat", "r+");
    fscanf(pFile, "%d", &nbElements);

    double X[nbElements];
    double Y[nbElements];

    printf("%d points\n", nbElements);
    for(int i = 0; i < nbElements; i++)
    {
        fscanf(pFile, "%lg", &X[i]);
        fscanf(pFile, "%lg", &Y[i]);

        // printf("%lg %lg\n", X[i], Y[i]);
    }
    
    double N[nbElements];
    differences_divises(N, X, Y, nbElements);

    // Je crois pas que cette prediction est pausible, donc, cette
    // methode d'interpolation n'est pas le meilleure pour la prediction
    // si la prediction est loin des premier points donnees ou la prediction 
    // est plausible, apres de certain an, il est pas plausible non plus
    // 
    // double est = 2007;
    // printf("Estimation de population pour %lg est : %lg\n", est, eval_p_dd(est, N, X, nbElements));

    for(int k = 0; k <= 1000; k++)
    {
        double zk = 2007 + ((10*(double)k) / 1000);
        printf("%lg %lg\n", zk, eval_p_dd(zk, N, X, nbElements));
    }
    
}