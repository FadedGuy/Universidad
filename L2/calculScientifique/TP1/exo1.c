//x^3 + 2x^2 -5x -6
#include <stdio.h>
#include <math.h>

double P_exo1(double xk)
{
    return((double)(xk*xk*xk) + 2*(xk*xk) - 5*xk -6);
}

int main()
{

    for(int k = 0; k <= 1000; k++)
    {
        double zk = -5 + ((10*(double)k) / 1000);
        printf("%g %g\n", zk, P_exo1(zk)); 
    }

    return 0;
}