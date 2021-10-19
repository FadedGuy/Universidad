#include "compte.h"

//Verifier si la compte est cloture
BOOL estCloture(Compte c1)
{
    return c1->estCloture;
}

//Creer un nouvelle compte
Compte creer()
{
    Compte c1 = malloc(sizeof(Compte));
    if(c1 == NULL)
    {
        fprintf(stderr, "Allocation impossible\n");
        exit(EXIT_FAILURE);
    }

    c1->solde = 0;
    c1->estCloture = FALSE;
    //A que se inicializa titulaire? Nunca se especifica
    c1->titulaire = NULL;
    return c1;
}

//Crediter un compte si c'est pas cloture
Compte crediter(Compte c1, float s1)
{
    if(!estCloture(c1))
    {
        c1->solde = c1->solde + s1;
    }
    else
    {
        fprintf(stderr, "Compte est cloture, impossible crediter\n");    
    }

    return c1;
}

//Debiter un compte si c'est pas cloture
Compte debiter(Compte c1, float s1)
{
    if(!estCloture(c1))
    {
        c1->solde = c1->solde - s1;
    }
    else
    {
        fprintf(stderr, "Compte est cloture, impossible debiter\n");    
    }

    return c1;
}

//Cloturer une compte si c'est pas deja cloture et si le solde est 0
Compte cloturer(Compte c1)
{
    if(!estCloture(c1) && c1->solde == 0)
    {
        c1->estCloture = TRUE;
    }
    else
    {
        if(estCloture(c1))
        {
            fprintf(stderr, "Compte est cloture, impossible de cloturer\n");    
        }
        else
        {
            fprintf(stderr, "Solde n'est pas 0, impossible de cloturer\n");
        }
    }

    return c1;
}

//Change ou initialise le titulaire de la compte (Extra?)
Compte changerTitulaire(Compte c1, char *titulaire)
{
    if(!estCloture(c1))
    {
        if(c1->titulaire == NULL)
        {
            c1->titulaire = malloc(strlen(titulaire));
            strcpy(c1->titulaire, titulaire);
        }
        else
        {
            c1->titulaire = realloc(c1->titulaire, strlen(titulaire));
            strcpy(c1->titulaire, titulaire);
        }

        if(strcmp(c1->titulaire, titulaire) != 0)
        {
            fprintf(stderr, "Impossible de changer le titulaire\n");
        }
    }
    else
    {
        fprintf(stderr, "Compte est cloture, impossible de changer titulaire\n");
    }

    return c1;
}

//Retourner le titulaire de la compte
char* titulaire(Compte c1)
{
    return c1->titulaire;
}

float solde(Compte c1)
{
    return c1->solde;
}
