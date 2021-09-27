#include "interpolation.h"
#include <stdio.h>

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
