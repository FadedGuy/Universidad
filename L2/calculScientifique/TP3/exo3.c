#include <stdio.h>
#include "matrice.h"

int main() {
    // Decomposition LU
    /*double A[] = {4, 2, 0,
                    4, 4, 2,
                    2, 2, 3};
    double L[9];
    double U[9];
    double verif[9];

    vecteurVide(L, 9);
    vecteurVide(U, 9);

    decompositionLU(A, L, U, 3);

    printf("Produit LU :\n");
    prodMM(L, U, verif, 3);
    afficheM(verif, 3); */
    

    // Systeme lineaire
    double A[] = {4, 2, 0,
                  4, 4, 2,
                  2, 2, 3};
    double b[] = {2, 4, 6};
    double x[3];
    double verif[3];

    resSystemeLineaire(A, b, x, 3);

    printf("A*x:\n");
    prodMV(A, x, verif, 3);
    afficheV(verif, 3);
    printf("b:\n");
    afficheV(b, 3);
    
    return 0; 
}