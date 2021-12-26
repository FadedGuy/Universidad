#include "arbre.h"
#include <stdio.h>

int main(){
    ARBRE a = arbreVide();
    FORET f = foretVide();
    element e = 5;

    if(!estArbreVide(a)){
        printf("Implementation de arbreVide incorrect\n");
        return 1;
    }

    a = construire(a, f, e);
    if(estArbreVide(a)){
        printf("Implementation de construire incorrect\n");
        return 1;
    }

    if(!estForetVide(f)){
        printf("Implementation de foretVide incorrect\n");
        return 1;
    }

    f = planter(f, 1, a);
    if(estForetVide(f)){
        printf("Implementation de planter incorrect\n");
        return 1;
    }

    if(racine(a)->etiquette != e){
        printf("Implementation de racine incorrect\n");
        return 1;
    }

    if(listeSousArbres(a) == f){
        printf("Implementation de listeSousArbres incorrect\n");
        return 1;
    }

    if(nbArbres(foretVide()) != 0){
        printf("Implementation de nbArbres incorrect\n");
        return 1;
    }

    if(nbArbres(f) != 1){
        printf("Implementation de nbArbres incorrect\n");
        return 1;
    }

    if(iemeArbre(f, 1) == a){
        printf("Implementation de iemeArbre incorrect\n");
        return 1;
    }

    printf("Implementation de type abstrait correct\n");
    return 0;
}