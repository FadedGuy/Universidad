#include "liste.h"

void printListe(liste l){
    liste lp = l;
    while(lp != NULL){
        printf("%d ", tete(lp));
        lp = lp->next;
    }
    printf("\n");
}

liste listeVide(){
    return NULL;
}

liste cons(Elem e, liste l){
    liste newL = malloc(sizeof(liste));
    if(newL == NULL){
        printf("Allocation impossible\n");
        exit(EXIT_FAILURE);
    }

    newL->element = e;
    newL->next = NULL;

    if(l == NULL){
        l = newL;
        return l;
    }else{
        newL->next = l;
    }   
    return newL;
}

Elem tete(liste l){
    return l->element;
}

liste fin(liste l){
    liste nListe = l->next;
    free(l);
    return nListe;
}

BOOL estVide(liste l){
    return l == NULL;
}