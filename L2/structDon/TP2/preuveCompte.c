#include "compte.h"
#include <string.h>
#include <stdio.h>

int main()
{
    BOOL success = TRUE;
    char* nom = "Jean Bap";
    float quantite = 505.5;

    //Creer 
    Compte compte = creer();
    if(compte->solde != 0 || compte->estCloture != FALSE)
        success = FALSE;

    if(success == FALSE)
    {
        fprintf(stderr, "Implementation incorrect du creer()\n");
        exit(EXIT_FAILURE);
    }

    //Crediter
    success = TRUE;
    if(compte->estCloture == FALSE)
    {
        compte = changerTitulaire(compte, nom); //Fonction extra prcq il y a pas d'initialisation du titulaire
        if(compte->solde+quantite != crediter(compte, quantite)->solde || strcmp(nom, crediter(compte, quantite)->titulaire) != 0)
        {
            success = FALSE;
        }
        crediter(compte, quantite);
    }
    else
    {
        fprintf(stderr, "Implementation incorrect du creer()\n");
        exit(EXIT_FAILURE);
    }

    if(success == FALSE)
    {
        fprintf(stderr, "Implementation incorrect du crediter()\n");
        exit(EXIT_FAILURE);
    }

    //Debiter
    success = TRUE;
    if(compte->estCloture == FALSE)
    {
        if(compte->solde-quantite != debiter(compte, quantite)->solde || strcmp(nom, debiter(compte, quantite)->titulaire) != 0)
        {
            success = FALSE;
        }
        debiter(compte, quantite);
    }
    else
    {
        fprintf(stderr, "Implementation incorrect du crediter()\n");
        exit(EXIT_FAILURE);
    }

    if(success == FALSE)
    {
        fprintf(stderr, "Implementation incorrect du debiter()\n");
        exit(EXIT_FAILURE);
    }

    //Cloture
    success = TRUE;
    if(compte->estCloture == FALSE && compte->solde == 0)
    {
        if(compte->estCloture == cloturer(compte)->estCloture || cloturer(compte)->solde != 0)
        {
            success = FALSE;
        }
        compte = cloturer(compte);
    }
    else
    {
        fprintf(stderr, "Implementation incorrect du crediter/debiter()\n");
        exit(EXIT_FAILURE);
    }
    if(success == FALSE)
    {
        fprintf(stderr, "Implementation incorrect du cloturer()\n");
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "Implementation correct du type\n");

    return 0;
}