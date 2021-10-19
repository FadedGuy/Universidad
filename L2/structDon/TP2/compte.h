#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Creation du bool
#define TRUE 1
#define FALSE 0
#define charBuffer 100
typedef int BOOL;

typedef struct s_Compte
{
    float solde;
    BOOL estCloture;
    char *titulaire;
}compte;

typedef struct s_Compte* Compte; 

BOOL estCloture(Compte);

Compte creer();
Compte crediter(Compte, float);
Compte debiter(Compte, float);
Compte cloturer(Compte);
Compte changerTitulaire(Compte, char*);

char* titulaire(Compte);
float solde(Compte);

