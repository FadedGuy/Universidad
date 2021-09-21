#include <stdio.h>
#include <math.h>

double fact(long num){
    double res = 1;
    for(int i = 2; i <= num; i++){
        res = res*i;
    }
    // printf("%d, %d\n", num, res);
    return res;
}

double sin_approx(double x, int N)
{
    //PETITE
    // double res = x;
    // for(int i = 1; i <= N; i++){
    //     int sign = pow(-1, i);
    //     double num = x*x;
    //     num = num*sign;
    //     double den = ((2*i)+1)*(2*i);
    //     res += num/den;
    //     // printf("%lf\n", num/den);
    // }

    //TEL QUE
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
    float x;
    printf("Donne x: ");
    scanf("%f", &x);
    printf("Sin = %lf\n",sin(x));
    printf("Approximation sin = %lf\n",sin_approx(x,N));
    printf("Difference = %lf\n", sin(x) - sin_approx(x,N));
    
    // printf("Difference = %lf\n", sin(x) - sin_approx(x,1));
    // printf("Difference = %lf\n", sin(x) - sin_approx(x,2));
    // printf("Difference = %lf\n", sin(x) - sin_approx(x,4));
    // printf("Difference = %lf\n", sin(x) - sin_approx(x,8));

    /*****************
     * RESULTATS AVEC LES VALEURS A 6 DECIMALS
     * Le rang de cette approximation est -2PI <= x <= 2PI
     * Apres de cette rang, les valeurs sont bon, mais il faut que
     * sont converti
     * N = 1, x = 0, d = 0 
     * N = 2, x = 0, d = 0
     * N = 4, x = 0, d = 0
     * N = 8, x = 0, d = 0
     *  
     * N = 1, x = PI (3.14159), d = 2.026113
     * N = 2, x = PI (3.14159), d = -0.524041
     * N = 4, x = PI (3.14159), d = -0.006925
     * N = 8, x = PI (3.14159), d = -0.000000
     * 
     * N = 1, x = PI/6 (0.52359), d = 0.000326
     * N = 2, x = PI/6 (0.52359), d = -0.000002
     * N = 4, x = PI/6 (0.52359), d = -0.000000
     * N = 8, x = PI/6 (0.52359), d = -0.000000
     * 
     * N = 1, x = 10PI (31.41592), d = 5136.293755
     * N = 2, x = 10PI (31.41592), d = -249879.855413
     * N = 4, x = 10PI (31.41592), d = -76402981.808341
     * N = 8, x = 10PI (31.41592), d = -61607359552.289543
     ****************/
}