#include <stdlib.h>
#include <stdio.h>
#ifndef ARBREFORET
#define ARBREFORET

#define TRUE 1
#define FALSE 0
typedef int BOOL;

typedef int element;

typedef struct noeud{
    element etiquette;
    int nb_sArbres;
    struct noued* sous_arbres[];
}*NOEUD;
typedef NOEUD ARBRE;

struct tree{
    ARBRE un_arbre;
    struct tree* suivant;
};
typedef struct tree* FORET;

ARBRE arbreVide();
ARBRE construire(NOEUD o, FORET f, element e);
BOOL estArbreVide(ARBRE a);
NOEUD racine(ARBRE a);

FORET foretVide();
BOOL estForetVide(FORET f);
FORET listeSousArbres(ARBRE a);
FORET planter(FORET f, int i, ARBRE a);
int nbArbres(FORET f);
ARBRE iemeArbre(FORET f, int i);

// typedef struct noeud{
//     element racine;
//     int nb_sArbres;
//     struct noeud* sous_arbre[];
// }*node;
// typedef node tree;

// typedef struct foret{
//     tree arbre;
//     struct foret* suivant;
// }*forest;

// tree arbreVide();
// tree construire(element, forest);
// forest foretVide();
// forest planter(tree, int, forest);

// BOOL estArbreVide(tree);
// BOOL estForetVide(forest);

// element racine(tree);
// forest listeSousArbres(tree);
// int nombreArbres(forest);
// tree iemeArbre(forest, int);

#endif