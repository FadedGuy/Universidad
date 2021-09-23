#include <stdio.h>
#include <math.h>

double fact(long num){
    double res = 1;
    for(int i = 2; i <= num; i++){
        res = res*i;
    }
    return res;
}

double sin_approx(double x, int N)
{
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
    const int N = 8;
    double x;
    printf("Donne x: ");
    scanf("%g", &x);

    printf("sin(%g) = %g\n", x, sin(x));
    printf("sin_approx(%g) = %g\n", x, sin_approx(x,N));
    printf("Difference = %g\n", sin(x) - sin_approx(x,N));
    

    //double x = 0;
    //double x = M_PI;
    //double x = M_PI/6;
    //double x = 10*M_PI;
    // printf("Difference = %g\n", sin(x) - sin_approx(x,1));
    // printf("Difference = %g\n", sin(x) - sin_approx(x,2));
    // printf("Difference = %g\n", sin(x) - sin_approx(x,4));
    // printf("Difference = %g\n", sin(x) - sin_approx(x,8));

    /*****************
     * RESULTATS AVEC LES VALEURS
     * 
     * N = 1, x = 0, d = 0 
     * N = 2, x = 0, d = 0
     * N = 4, x = 0, d = 0
     * N = 8, x = 0, d = 0
     *  
     * N = 1, x = PI, d = 2.02612
     * N = 2, x = PI, d = -0.524044
     * N = 4, x = PI, d = -0.00692527
     * N = 8, x = PI, d = -2.24195e-08
     * 
     * N = 1, x = PI/6, d = 0.000325821
     * N = 2, x = PI/6, d = -2.13259e-06
     * N = 4, x = PI/6, d = -2.02799e-11
     * N = 8, x = PI/6, d = 0
     * 
     * N = 1, x = 10PI, d = 5136.3
     * N = 2, x = 10PI, d = -249880
     * N = 4, x = 10PI, d = -7.64031e+07
     * N = 8, x = 10PI, d = -6.16076e+10
     ****************/
}