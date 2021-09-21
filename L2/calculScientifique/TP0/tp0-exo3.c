#include <stdio.h>
#include <math.h>

long fact(long num){
    long res = 1;
    for(int i = 2; i <= num; i++){
        res = res*i;
    }
    // printf("%d, %d\n", num, res);
    return res;
}

double sin_approx(double x, int N)
{
    /*double res = x;
    for(int i = 1; i <= N; i++){
        int sign = pow(-1, i);
        double num = x*x;
        num = num*sign;

        double den = ((2*i)+1)*(2*i);
        res = res + num/den;
    }*/

    double res = x;
    for(int i = 1; i <= N; i++){
        double num = pow(x, (double)((2*i)+1));
        double den = fact((2*i)+1);
        long sign = pow((long)-1, i);
        res = res + (num*sign)/(den);
    }

    return res;
}

int main()
{
    const int N = 100;
    float x;
    printf("Donne x: ");
    scanf("%f", &x);
    printf("Sin = %lf\n",sin(x));
    printf("Approximation sin = %lf\n",sin_approx(x,N));
    printf("Difference = %lf\n", sin(x) - sin_approx(x,N));
    //printf("Difference = %lf\n", sin(x) - sin_approx(x,1));
    //printf("Difference = %lf\n", sin(x) - sin_approx(x,2));
    //printf("Difference = %lf\n", sin(x) - sin_approx(x,4));
    //printf("Difference = %lf\n", sin(x) - sin_approx(x,8));

    /*****************
     * RESULTATS AVEC LES VALEURS ()CHANGER
     * N = 1, x = 0, d = 0 
     * N = 2, x = 0, d = 0
     * N = 4, x = 0, d = 0
     * N = 8, x = 0, d = 0
     *  
     * N = 1, x = PI, d = 2.026141
     * N = 2, x = PI, d = 3.02010
     * N = 4, x = PI, d = 2.632248
     * N = 8, x = PI, d = 2.516027
     * 
     * N = 1, x = PI/6, d = 0.000326
     * N = 2, x = PI/6, d = -0.006524
     * N = 4, x = PI/6, d = -0.005133
     * N = 8, x = PI/6, d = -0.004609
     * 
     * N = 1, x = 10*PI, d = 5136.296579
     * N = 2, x = 10*PI, d = 258602.364237
     * N = 4, x = 10*PI, d = -85574434.467789
     * N = 8, x = 10*PI, d = -85597422066.085764
     ****************/
}