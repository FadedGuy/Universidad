#include <stdlib.h>
#include <stdio.h>

//Creation du bool
#define TRUE 1
#define FALSE 0
typedef int BOOL;

typedef int Elem;

typedef struct s_liste{
    Elem element;
    struct s_liste *next;
}*liste;

void printListe(liste);

liste listeVide();
liste cons(Elem, liste);
liste fin(liste);

Elem tete(liste);
BOOL estVide(liste);
