#include <stdio.h>

#include "matrice.h"

int main() {
    
    // Verification descente
    /*
    double L[] = {1, 0, 0, 
                    1, 1, 0,
                    0.5, 0.5, 1,};
    double b[] = {2, 4, 6};
    double verif[3];
    double y[3];
    
    vecteurVide(y, 3);

    descente(L, b, y, 3);

    printf("Vecteur y: \n");
    afficheV(y, 3);

    printf("Verif Ly = : \n");
    prodMV(L, y, verif, 3);
    afficheV(verif, 3); 
    */

    
    // Verification remontee
    
    double U[] = {4, 2, 0,
                    0, 2, 2,
                    0, 0, 2};
    double y[] = {2, 2, 4};
    double verif[3];
    double x[3];
    
    vecteurVide(x, 3);

    remontee(U, y, x, 3);

    printf("Vecteur x: \n");
    afficheV(x, 3);

    printf("Verif Ux = : \n");
    prodMV(U, x, verif, 3);
    afficheV(verif, 3);
    
    return 0; 
}