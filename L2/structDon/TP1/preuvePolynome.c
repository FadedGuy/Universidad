#include "polynome.c"

int main(int argc, char* argv[])
{
    POLYNOME p1, p2;
    float a0;
    BOOL succes;
    p1 = malloc(sizeof(POLYNOME));
    p2 = malloc(sizeof(POLYNOME));
    if(p1 == NULL || p2 == NULL)
    {
        printf("Allocation impossible\n");
        exit(EXIT_FAILURE);
    }

    p1 = nul();
    succes = TRUE;
    if(!estNul(p1))
        succes = FALSE;
    
    if(degre(p1) != 0)
        succes = FALSE;

    for(int i = 0; i < MAX_SIZE; i++)
    {
        if(coefficient(p1, i) != 0)
        {
            succes = FALSE;
        }
    }

    if(succes == FALSE)
    {
        printf("\nImplementation incorrecte du constructer nul()\n");
        printf("Interruption de la verification : revoir l'implementation du type abstrait\n");
        exit(EXIT_FAILURE);
    }

    p2 = construire(p1, a0);
    succes = TRUE;

    if(estNul(p1))
    {
        if(estNul(p2) && a0 == 0)
        {
            succes = FALSE;
        }
    }
    if(estNul(p2) && a0 == 0)
    {
        if(estNul(p1))
        {
            succes = FALSE;
        }
    }

    if(succes == FALSE)
    {
        printf("\nImplementation de Construire(estNul) incorrecte\n");
        printf("Interruption de la verification : revoir l'impolementation du type abstrait\n");
        exit(EXIT_FAILURE);
    }


    succes = TRUE;
    if(degre(p1) == 0)
    {
        if(estNul(p2))
        {
            succes = FALSE;
        }
    }

    if(estNul(p2))
    {
        if(degre(p1) == 0) 
        {
            succes = FALSE;
        }
    }

    if(degre(p1) == degre(p2)+1)
    {
        if(!estNul(p2))
        {
            succes = FALSE;
        }
    }
    if(!estNul(p2))
    {
        if(degre(p1) == degre(p2)+1)
        {
            succes = FALSE;
        }
    }

    if(succes == FALSE)
    {
        printf("\nImplementation de Construire(degre) incorrecte\n");
        printf("Interruption de la verification : revoir l'impolementation du type abstrait\n");
        exit(EXIT_FAILURE);
    }

    succes = TRUE;
    if(coefficient(p2, 0) != a0)
    {
        succes = FALSE;
    }
    if(estNul(p1))
    {
        for(int i = 1; i < MAX_SIZE; i++)
        {
            if(coefficient(p2, i) != coefficient(p1, i-1))
            {
                succes = FALSE;
            }
        }
    }
    if(estNul(p2))
    {
        for(int i = degre(p2)+2; i <= MAX_SIZE; i++)
        {
            if(coefficient(p1, i) != 0)
            {
                succes = FALSE;
            }
        }
    }

    if(succes == FALSE)
    {
        printf("\nImplementation de Construire(coefficient) incorrecte\n");
        printf("Interruption de la verification : revoir l'impolementation du type abstrait\n");
        exit(EXIT_FAILURE);
    }

    printf("L'implementation du type asbtrait est verifiee\n");
    printf("Fin normale de la verification de l'implementation du type abstrait\n");
    return EXIT_SUCCESS;
}