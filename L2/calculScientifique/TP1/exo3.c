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

    // printf("%d points\n", nbElements);
    for(int i = 0; i < nbElements; i++)
    {
        fscanf(pFile, "%lg", &X[i]);
        fscanf(pFile, "%lg", &Y[i]);

        // printf("%lg %lg\n", X[i], Y[i]);
    }

    double N[nbElements];
    differences_divises(N, X, Y, nbElements);

    double est = 1998;
    printf("\nEstimation de population pour %lg est : %lg\n", est, eval_p_dd(est, N, X, nbElements));

    // Verifier que tous les points sont bon, mais il existe l'erreur 
    // d'intepolation polynomiale a partir du troisieme terme.
    // printf("Annee,Population  Estimation\n");
    // for(int i = 0; i < nbElements; i++)
    // {
    //     printf("%lg,%lg   %lg\n", X[i], Y[i], eval_p_dd(X[i], N, X, nbElements));
    // }
    return 0;
}