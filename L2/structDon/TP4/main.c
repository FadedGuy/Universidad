#include "arbre.h"
#include <stdio.h>

int main(){
    tree t = arbreVide();
    forest f = foretVide();

    if(!estArbreVide(t)){
        printf("Implementation du arbreVide incorrect\n");
    }
    if(!estForetVide(f)){
        printf("Implementation du foretVide incorrect\n");
    }
    printf("%d",nombreArbres(f));
    t = construire(15, f);
    // f = planter(t, 15, f);

    if(estArbreVide(t)){
        printf("Implementation du construire incorrect\n");
    }
    if(estForetVide(f)){
        printf("Implementation du planter incorrect\n");
    }

    printf("\nL'implémentation du type abstrait est vérifiée.");
    printf("\nFin normale de la vérification de l'implémentation du type abstrait.\n");

    return 0;
}