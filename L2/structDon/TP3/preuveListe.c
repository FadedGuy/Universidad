#include "liste.h"
#include <stdio.h>

int main(){
    Elem e = 15;
    liste l = listeVide();
    if(estVide(l) == FALSE){
        printf("Implementation incorrect de listeVide()\n");
        exit(EXIT_FAILURE);
    }

    l = cons(e, l);
    if(estVide(l) == TRUE){
        printf("Implementation incorrect de cons()\n");
        exit(EXIT_FAILURE);
    }

    if(estVide(l) == FALSE){
        if(tete(cons(e, l)) != e){
            printf("Implementation incorrect de tete()\n");
            exit(EXIT_FAILURE);
        }
    }else{
        printf("Implementation incorrect de cons()\n");
        exit(EXIT_FAILURE);
    }

    if(estVide(l) == FALSE){
        if(fin(cons(e, l)) != l){
            printf("Implementation incorrect de fin()\n");
            exit(EXIT_FAILURE);
        }
    }else{
        printf("Implementation incorrect de cons()\n");
        exit(EXIT_FAILURE);
    }


    printf("Implementation correct de liste\n");
    free(l);
    return 0;
}