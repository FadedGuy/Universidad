#include <stdio.h>
#include <math.h>

double sin_approx(double x, int N)
{
    double res = x;
    for(int i = 1; i <= N; i++){
        double num = x*x, den = (((2*i)+1) * (2*i));
        if(i % 2 == 0){
            res += ((num/den)*res);
        }else{
            res -= ((num/den)*res);
        }
    }
    return res;
}

int main()
{
    const int N = 200;
    float x;
    printf("Donne x: ");
    scanf("%f", &x);

    // printf("Sin = %lf\n", sin(x));
    // printf("Approximation = %lf\n", sin_approx(x,N));
    printf("Difference = %lf", sin(x) - sin_approx(x,N));
}