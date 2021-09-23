#include <stdio.h>
#include <math.h>

int main()
{
    long emprunt = 200000;
    double tauxAnnuelHors = 1.32;
    int ans = 20;

    double tauxAnnuelAvec = pow((1 + tauxAnnuelHors/100), (double)1/12) - 1;
    double mensualite = ((emprunt * tauxAnnuelAvec) * pow(1 + tauxAnnuelAvec, (double)12*ans))/ (pow(1 + tauxAnnuelAvec, (double)12*ans) - 1);
    
    double interet = 0, rembourse = 0;

    printf("Mois    Mensualite  Interets    CapitalRembourse    CapitalDu\n");
    for(int i = 1; i <= ans*12; i++)
    {
        interet = tauxAnnuelAvec * (emprunt - rembourse);
        rembourse += mensualite-interet;
        printf("%d   |   %.2f   |   %.2f   |   %.2f   |   %.2f\n", i, mensualite, interet, rembourse, emprunt-rembourse);
    }
}