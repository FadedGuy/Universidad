#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Creer vecteur vide */
void vecteurVide(double *x, int n);

/* Afficher vecteur */
void afficheV(double *x, int n);

/* Afficher matrice */ 
void afficheM(double *A, int n);

/* Produit matrice vecteur */
void prodMV(double *A, double *x, double *y, int n);

/* Produit matrice matrice */
void prodMM(double *A, double *B, double *C, int n);

/* Methode descente */
void descente(double *L, double *b, double *y, int n);
 
/* Methode remonte */
void remontee(double *U, double *y, double *x, int n);

/* decomposition LU */
void decompositionLU(double *A, double *L, double *U, int n);

/* Resoudre systeme lineaire */
void resSystemeLineaire(double *A, double *b, double *x, int n);