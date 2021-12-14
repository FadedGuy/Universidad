#include <stdlib.h>
#ifndef ARBRE
#define ARBRE

#define TRUE 1
#define FALSE 0
typedef int BOOL;

typedef int element;

typedef struct noeud{
    element etiquette;
    int nb_sArbres;
    struct noeud* sous_arbre[];
}*node;
typedef node tree;

typedef struct foret{
    tree arbre;
    struct tree* suivant;
}*forest;


tree arbreVide();
tree construire(tree);
forest foretVide();
forest planter(tree, int, forest);

BOOL estArbreVide(tree);
BOOL estForetVide(forest);

element racine();
forest listeSousArbres(tree);
int nombreArbres(forest);
tree iemeArbre(forest, int);

#endif