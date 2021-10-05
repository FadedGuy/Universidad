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

    for(int i = 1; i < n; i++)
    {
        for(int j = n-1; j > i; j--)
        {
            N[i+n] = eval_p_dd(X[j], N, X, n);
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
}
