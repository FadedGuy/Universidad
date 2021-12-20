#include "arbre.h"

tree arbreVide(){
    return NULL;
}

tree construire(element e, forest f){
    forest foret = f;
    tree t;

    t = malloc(sizeof(struct noeud));
    if(t == NULL){
        fprintf(stderr, "Allocation impossible\n");
        exit(EXIT_FAILURE);
    }

    t->racine = e;
    t->nb_sArbres = nombreArbres(f);

    for(int i = 1; i <= t->nb_sArbres; i++){
        t->sous_arbre[i] = foret->arbre;
        foret = foret->suivant;
    }
    return t;
}

forest foretVide(){
    return NULL;
}

forest planter(tree t, int nb, forest f){
    forest foret = f;
    forest temp;

    for(int i = 1; i < nb; i++){
        foret = foret->suivant;
    }

    temp = malloc(sizeof(tree));
    temp = foret;

    foret->arbre = t;
    foret->suivant = temp;
    
    return foret;    
}

BOOL estArbreVide(tree t){
    return t == NULL;
}

BOOL estForetVide(forest f){
    return f == NULL;
}

element racine(tree t){
    return t->racine;
}

forest listeSousArbres(tree t){
    forest foret;
    
    foret = malloc(sizeof(tree));
    for(int i = 1; i<=t->nb_sArbres; i++){
        foret->arbre = t->sous_arbre[i];
        foret = foret->suivant;
    }

    return foret;
}

int nombreArbres(forest f){
    int res=0;
    forest foret = f;
        printf("Implementation du arbreVide incorrect\n");

    while(foret->arbre != NULL){
        res++;
        foret = foret->suivant;
    }
        printf("Implementation du arbreVide incorrect\n");

    return res;
}

tree iemeArbre(forest f, int nb){
    forest foret = f;

    for(int i = 1; i < nb; i++){
        foret = foret->suivant;
    }

    return foret->arbre;
}