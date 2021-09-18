#include <stdio.h>

double sin_approx(double x, int N)
{
    double un=1, res=0, num = x*x;

    for(int n = 2; n <= N; n++){
        double num = x*x, den = ((2*n)+1)*(2*n);
        //num = x^2
        //den = (2n+1)(2n)
        num = num*un;
        un = num/den;
        if(n % 2 != 0){
            un = un * -1;
        }

        res += un;
    }

    return res;
}

int main()
{
    const int N = 200;
    float x;
    printf("Donne x: ");
    scanf("%f", &x);

    printf("%f\n", sin_approx(x,N));
}