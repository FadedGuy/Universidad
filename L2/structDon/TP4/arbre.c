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


// tree arbreVide(){
//     return NULL;
// }

// tree construire(element e, forest f){
//     forest foret = f;
//     tree t;

//     t = malloc(sizeof(struct noeud));
//     if(t == NULL){
//         fprintf(stderr, "Allocation impossible\n");
//         exit(EXIT_FAILURE);
//     }

//     t->racine = e;
//     t->nb_sArbres = nombreArbres(f);

//     for(int i = 1; i <= t->nb_sArbres; i++){
//         t->sous_arbre[i] = foret->arbre;
//         foret = foret->suivant;
//     }
//     return t;
// }

// forest foretVide(){
//     return NULL;
// }

// forest planter(tree t, int nb, forest f){
//     forest foret = f;
//     forest temp;

//     for(int i = 1; i < nb; i++){
//         foret = foret->suivant;
//     }

//     temp = malloc(sizeof(tree));
//     temp = foret;

//     foret->arbre = t;
//     foret->suivant = temp;
    
//     return foret;    
// }

// BOOL estArbreVide(tree t){
//     return t == NULL;
// }

// BOOL estForetVide(forest f){
//     return f == NULL;
// }

// element racine(tree t){
//     return t->racine;
// }

// forest listeSousArbres(tree t){
//     forest foret;
    
//     foret = malloc(sizeof(tree));
//     for(int i = 1; i<=t->nb_sArbres; i++){
//         foret->arbre = t->sous_arbre[i];
//         foret = foret->suivant;
//     }

//     return foret;
// }

// int nombreArbres(forest f){
//     int res=0;
//     forest foret = f;
//         printf("Implementation du arbreVide incorrect\n");

//     while(foret->arbre != NULL){
//         res++;
//         foret = foret->suivant;
//     }
//         printf("Implementation du arbreVide incorrect\n");

//     return res;
// }

// tree iemeArbre(forest f, int nb){
//     forest foret = f;

//     for(int i = 1; i < nb; i++){
//         foret = foret->suivant;
//     }

//     return foret->arbre;
// }