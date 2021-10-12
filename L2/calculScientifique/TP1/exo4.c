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

    // Je crois pas que cette prediction est pausible, donc, cette
    // methode d'interpolation n'est pas le meilleure pour la prediction
    // si la prediction est loin des premier points donnees ou la prediction 
    // est plausible, sinon c'est pas plausible
    
    // double est = 2018;
    // printf("Estimation de population pour %lg est : %lg\n", est, eval_p_dd(est, N, X, nbElements));


    // L'evolution dans les intervales [2007; 2008] et [2016;2017] ne sont pas raisonnables a 
    // mon avis, le change de direction et decrement est pas posible, ca donne feu a pourquoi
    // la prediction pour 2018 ne fait pas de sense du tout. C'est pour cette motif aussi que
    // dehors du rang de la fonction on utilise l'extrapolation, pas l'interpolation
    for(int k = 0; k <= 1000; k++)
    {
        double zk = 2007 + ((10*(double)k) / 1000);
        printf("%lg %lg\n", zk, eval_p_dd(zk, N, X, nbElements));
    }
    return 0; 
}