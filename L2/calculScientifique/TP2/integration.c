#include "integration.h"
#include <stdio.h>

double integrationPtMilieu(double (*f)(double), double a, double b)
{
    return (b-a)*f((a+b)/2);
}

double integrationPtMilieuComposite(double (*f)(double), double a, double b, int N)
{
    double res = 0;
    double ci = a + (i * ((b-a)/N)); //Interior for
    double cx = a;
    for(int i = 0; i < N; i++)
    {
        res += (integrationPtMilieu(f, cx, cx+ci) * f(cx));
        printf("%lg\n", cx);
        cx+=ci;
    }

    return res;
}