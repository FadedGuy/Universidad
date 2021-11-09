#include "integration.h"
#include <stdio.h>
#include <math.h>

double sinx(double x)
{
    return sin(x);
}

int main()
{
    double a = 0;
    double b = M_PI;
    printf("N PtMilieu Trapeze Simpson\n");
    for(int i=2; i <= 15; i++)
    {
        printf("%d %.18lf %.18lf %.18lf\n", i, fabs(2 - integrationPtMilieuComposite(&sinx, a, b, i)), fabs(2-integrationTrapezeComposite(&sinx, a, b, i)), fabs(2 - integrationSimpson(&sinx, a, b, i)));
    }

    /*******************
     * 
     * On peut dire que l'ordre numerique du ptMilieu est de deuxieme degre
     * la formule des trapeces est de premier degre comme on peut constater sur
     * la graphe des erreur. Et la formule de Simpson est de quatrieme degre.
     * 
     * Le methode le plus efficace est le methode de Simpson car on obtiens l'erreur 
     * le plus petite, apres c'est la formule de ptMilieu et la moins efficace la formule
     * des trapeces. Le plus grand le degre, le moins petite l'erreur et le plus efficace.
     * 
     * *****************/

    return 0;
}

