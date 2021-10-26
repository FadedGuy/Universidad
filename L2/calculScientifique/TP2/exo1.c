#include "integration.h"
#include <stdio.h>
#include <math.h>

double sinx(double x)
{
    return sin(x);
}

int main()
{
    printf("%.10lf\n",integrationPtMilieu(&sinx, 0, M_PI));
    for(int i=2; i <= 5; i++)
    {
        printf("%.10lf\n",integrationPtMilieuComposite(&sinx, 0, M_PI, i));
    }

    return 0;
}

