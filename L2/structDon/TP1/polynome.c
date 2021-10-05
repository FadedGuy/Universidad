#include "polynome.h"

//Sera il mieux de creer un nouvelle fonction pour savoir si l'allocation memoire avec p etait possible? 
//On peut factoriser le code.

POLYNOME nul()
{
    POLYNOME p;
    p = malloc(sizeof(struct s_polynome));
    if(p == NULL)
    {

        fprintf(stderr, "Allocation impossible\n");
        exit(EXIT_FAILURE);
    }
    else 
    {
        //Est-il possible d'utiliser . en lieu de  -> ? 
        p -> degre = 0;
        for(int i = 0 ; i <= MAX_SIZE; i++)
        {
            p -> coefficient[i] = 0;
        }

    }
    return p;
}

POLYNOME construire(POLYNOME p1, float a0)
{
    POLYNOME p;
    p = malloc(sizeof(struct s_polynome));
    if(p == NULL)
    {

        fprintf(stderr, "Allocation impossible\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        if(estNul(p1))
        {
            p -> degre = 0;
            p -> coefficient[0] = a0;
            for(int i = 1; i <= MAX_SIZE-1; i++)
            {
                p -> coefficient[i] = 0; 
            }
        }
        else
        {
            p -> degre = p1 -> degre+1;
            p -> coefficient[0] = a0;
        }
    }
}

BOOL estNul(POLYNOME p1)
{

}

int degre(POLYNOME p1)
{

}

int coefficient(POLYNOME p1, int i)
{

}
