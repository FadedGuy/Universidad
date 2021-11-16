#include "integration.h"
#include <stdio.h>

/* Sabemos que la derivada de x^3 es 3x^2 */

double simpson(double (*f)(double), double a, double b, int N)
{
    double difX = (b-a)/N;
    double actX = a;
    double res = 0;
    for(int i = a; i < N; i++){

        actX += difX;
    }
    return (difX/3)*res;
}

double woo(double x){
    return 3*(x*x);
}

int main(){
    double a = 0;
    double b = 1;
    printf("%lf", simpson(&woo, a, b, 32));
}