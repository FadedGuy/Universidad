#include "polynome.h"

//Creer une polynome nul
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
        p->degre = 0;
        for(int i = 0 ; i <= MAX_SIZE; i++)
        {
            p -> coefficient[i] = 0;
        }

    }
    return p;
}

//Construire un polynome non nul
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
            //Decaler les coefficient qui existe deja
            for(int i = 1; i <= p1->degre; i++)
            {
                p -> coefficient[i] = p1 -> coefficient[i-1];
            }
            //Mettre le reste des coefficients a 0
            for(int i = p1->degre+2; i <= MAX_SIZE; i++)
            {
                p->coefficient[i] = 0; 
            }
        }
    }
    return p;
}

//Tester si un polynome est nul
BOOL estNul(POLYNOME p1)
{
    if(p1 != NULL && p1 -> degre != 0)
    {
        return FALSE;
    }
    for(int i = 0; i <= p1->degre; i++)
    {
        if(p1->coefficient[i] != 0)
            return FALSE;
    }
    return TRUE;
}

//Calculer le degre du polynome
float degre(POLYNOME p1)
{
    return p1->degre;    
}

//Calculer le coefficient i du polynome
float coefficient(POLYNOME p1, int i)
{
    return i < MAX_SIZE ? p1->coefficient[i] : 0;
}
