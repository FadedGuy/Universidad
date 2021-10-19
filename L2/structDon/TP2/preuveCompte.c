#include "compte.h"

int main()
{
    Compte compte = creer();
    printf("%f", compte->solde);

    return 0;
}