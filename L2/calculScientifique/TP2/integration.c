#include "integration.h"
#include <stdio.h>

double integrationPtMilieu(double (*f)(double), double a, double b)
{
    return (b-a)*(f((a+b)/2));
}

double integrationPtMilieuComposite(double (*f)(double), double a, double b, int N)
{
    double res = 0;
    double cx = a;
    for(int i = 0; i <= N; i++)
    {
        double ci = a + (i*((b-a)/N));
        res += integrationPtMilieu(f, cx, ci);
        cx = ci;
    }

    return res;
}

double integrationTrapezeComposite(double (*f)(double), double a, double b, int N)
{
    double res = 0;
    double cx = a;
    for(int i = 0; i <= N; i++)
    {
        double ci = a + (i*((b-a)/N));
        res += ((ci-cx)/2)*(f(ci)+f(cx));
        cx = ci;
    }
    return res;
}

double integrationSimpson(double (*f)(double), double a, double b, int N)
{
    double res = 0;
    double aa = a;
    for(int i = 0; i <= N; i++)
    {
        double bb = a + (i * ((a+b)/N));
        res += (((bb-aa)/6) * (f(aa) + (4*f((aa+bb)/2)) + f(bb)));
        // res += (f(bb) * ((2*(bb-aa))/3));
        aa = bb;
    }
    return res;
}