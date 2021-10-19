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

    for(int i = 1; i < n; i++)
    {
        for(int j = n; j >= i; j--)
        {
            N[j] = ((N[j] - N[j-1]) / (X[j] - X[j-i]));
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

double par_morceaux(double x, double *X, double *Y, int n, int degre)
{
    if(degre == 1 || degre == 2)
    {
        int i = degre;
        //Trouver le rang pourlequelle faire l'interpolation
        while(i < n && !(x <= X[i] && x >= X[i-degre]))
        {
            i+=degre;
        }
        // f(x) = ax^2 + bx + c

        if(i < n)
        {
            if(degre == 1) //Interpolation lineaire
            {
                // f(x) = mx + b
                // f(x) = f(n i) + (f(n i+1) - f(n i) / (x i+1) - (x i)) * (x - x i)  
                // pour X[min] <= x <= X[max] 
                return (double)(Y[i-1] + (((Y[i]- Y[i-1]) / (X[i] - X[i-1])) * (x-X[i-1])));
            }

            //Interpolation quadratique
            return (double)(Y[i-2] + 
                            (((Y[i-1] - Y[i-2]) / (X[i-1] - X[i-2])) * (X[i-1] - X[i-2])) + 
                            (((((Y[i] - Y[i-1]) / (X[i] - X[i-1])) - ((Y[i-1] - Y[i-2]) / (X[i-1] - X[i-2]))) / 
                                (X[i] - X[i-2])) * (x-X[i-2]) * (x-X[i-1])));
        }
        else
        {   
            printf("%lg dehors le rang [%lg;%lg]\n", x, X[0], X[n-1]);
            return 0;
        }
    }
    
    printf("%d degre d'interpolation non valide\n", degre);
    return 0;

}
