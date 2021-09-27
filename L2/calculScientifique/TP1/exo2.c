#include <stdio.h>
#include "interpolation.h"

int main()
{

    double X[] = {25, 40, 50, 60};
    double Y[] = {95, 75, 63, 54};

    printf("Vie de ventilateur estime pour %d est de: %g heures(x1000)\n", 30, eval_p_lagrange(30, X, Y, 4));
    printf("Vie de ventilateur estime pour %d est de: %g heures(x1000)\n", 45, eval_p_lagrange(45, X, Y, 4));
    printf("Vie de ventilateur estime pour %d est de: %g heures(x1000)\n", 70, eval_p_lagrange(70, X, Y, 4));

    return 0;
}