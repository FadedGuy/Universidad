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

    // printf("%d points\n", nbElements);
    for(int i = 0; i < nbElements; i++)
    {
        fscanf(pFile, "%lg", &X[i]);
        fscanf(pFile, "%lg", &Y[i]);

        // printf("%lg %lg\n", X[i], Y[i]);
    }
    
    double N[nbElements];
    differences_divises(N, X, Y, nbElements);

    // Je crois pas que cette prediction est pausible, cette
    // methode d'interpolation n'est pas bon quand le point a faire
    // une prediction c'est dehors le rang qui nous á, si jamais on veux faire un
    // prediction dehors le rang on doit faire l'extrapolation
    
    double est = 2018;
    printf("Estimation de population pour %lg est : %lg\n", est, eval_p_dd(est, N, X, nbElements));


    // Les evolution sur les intervales me semble raisonnables, ils sont pas de tout
    // impossible si un annee est mauvais ou tres bien pour la production
    // for(int k = 0; k <= 1000; k++)
    // {
    //     double zk = 2007 + ((10*(double)k) / 1000);
    //     printf("%lg %lg\n", zk, eval_p_dd(zk, N, X, nbElements));
    // }
    return 0; 
}