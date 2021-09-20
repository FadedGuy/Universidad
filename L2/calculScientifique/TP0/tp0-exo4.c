#include <stdio.h>
#include <math.h>

int main()
{
    long emprunt = 200000;
    float tauxAnnuelHors = 1.32;
    int ans = 20;

    float tauxAnnuelAvec = pow((1 + tauxAnnuelHors/100), (float)1/12) - 1;
    float mensualite = ((emprunt * tauxAnnuelAvec) * pow(1 + tauxAnnuelAvec, (float)12*ans))/ (pow(1 + tauxAnnuelAvec, (float)12*ans) - 1);
    
    float interet = tauxAnnuelAvec * (emprunt), rembourse = mensualite-interet;

    printf("Mois    Mensualite  Interets    CapitalRembourse    CapitalDu\n");
    for(int i = 1; i <= ans*12; i++)
    {
        printf("%d   |   %.2f   |   %.2f   |   %.2f   |   %.2f\n", i, mensualite, interet, rembourse, emprunt-rembourse);
        interet = tauxAnnuelAvec * (emprunt - rembourse);
        rembourse += mensualite-interet;
    }
}