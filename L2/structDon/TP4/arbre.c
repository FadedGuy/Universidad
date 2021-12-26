#include "arbre.h"

ARBRE arbreVide(){
    return NULL;
}

ARBRE construire(NOEUD o, FORET f, element e){
    FORET foret = f;
    ARBRE a;

    a = malloc(sizeof(struct noeud));
    if(a == NULL){
        fprintf(stderr, "Allocation impossible\n");
        exit(EXIT_FAILURE);
    }
    a->etiquette = e;
    a->nb_sArbres = nbArbres(f);

    for(int i = 1; i <=a->nb_sArbres; i++){
        a->sous_arbres[i] = foret->un_arbre;
        foret = foret->suivant;
    }
    return a;
}

BOOL estArbreVide(ARBRE a){
    return a==NULL;
}

NOEUD racine(ARBRE a){
    return a;
}

FORET foretVide(){
    return NULL;
}

BOOL estForetVide(FORET f){
    return f==NULL;
}

FORET listeSousArbres(ARBRE a){
    FORET f, foret;
    if(a->nb_sArbres == 0){
        return foretVide();
    } else{
        f = malloc(sizeof(struct tree));
        foret = f;
        if(foret == NULL){
            fprintf(stderr, "Allocation impossible\n");
            exit(EXIT_FAILURE);
        }

        for(int i = 1; i <= a->nb_sArbres; i++){
            foret->un_arbre = a->sous_arbres[i];
            foret->suivant = malloc(sizeof(struct tree));
            foret = foret->suivant;
        }
        foret = NULL;
    }

    return f;
}

FORET planter(FORET f, int i, ARBRE a){
    FORET first, new, actual, before;
    if(i == 1){
        first = malloc(sizeof(struct tree));
        first->un_arbre = &a;
        first->suivant = f;
        f = first;
    } else{
        actual = f;
        for(int i = 1; i <= i-1; i++){
            before = actual;
            actual = actual->suivant;
        }
        new = malloc(sizeof(struct tree));
        before->suivant = new;
        new->un_arbre = a;
        new->suivant = actual;
    }

    return f;
}

int nbArbres(FORET f){
    FORET foret = f;
    int nb = 0;
    while(foret != NULL){
        nb++;
        foret = foret->suivant;
    }
    return nb;
}

ARBRE iemeArbre(FORET f, int i){
    FORET foret = f;
    
    for(int i = 1; i<= i-1; i++){
        foret = foret->suivant;
    }
    return foret->un_arbre;
}

