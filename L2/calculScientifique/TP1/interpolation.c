#include <stdio.h>
#include "interpolation.h"

double base_lagrange(double x, int i, double *X, int n)
{
    double l = 1;
    for(int j = 0; j < n; j++)
    {
        if(j != i)
        {
            l = l * (double)((x-X[j]) / (X[i]-X[j]));
        }
    }
    return l;
}

double eval_p_lagrange(double x, double *X, double *Y, int n)
{
    double p = 0;
    for(int i = 0; i < n; i++)
    {
        p += Y[i] * base_lagrange(x, i, X, n);
    }
    return p;
}

void differences_divises(double *N, double *X, double *Y, int n)
{
    for(int i = 0; i < n; i++)
    {
        N[i] = Y[i];
    }

    for(int i = 1; i <= n-1; i++)
    {
        for(int j = n-1; j >= i; j--)
        {
            N[j] = ((N[j] - N[j-1]) / (X[j] - X[j-1]));
        }
    }
}

double eval_p_dd(double x, double *N, double *X, int n)
{
    double p = N[0];
    double q = 1;

    for(int i = 1; i < n; i++)
    {
        q = q * (x-X[i-1]);
        p = p + (q * N[i]);
    }
    return p;
}

double par_morceaux(double x, double *X, double *Y, int n)
{
    int i = 1;
    while(i < n && !(x <= X[i] && x >= X[i-1]))
    {
        i++;
    }

    if(i < n)
    {
        return (double)(Y[i-1] + (((Y[i]- Y[i-1]) / (X[i] - X[i-1])) * (x-X[i-1])));
    }
    else
    {   
        printf("%lg dehors le rang [%lg;%lg]\n", x, X[0], X[n-1]);
        return 0;
    }
}
