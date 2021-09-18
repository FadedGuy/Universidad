#include <math.h>
#include <stdio.h>

//N=0 1
//N=1 0.987
//N=2 0.974169
//N=10 0.877347

int main()
{
    int n;
    float q=0.987;
    float u0=1;
    float u=u0;
    printf( " Saisir la valeur de n : ");
    scanf("%d", &n);
    for (int i=0;i<n;i++)
    {
        u = u * q;
    }

    float qn = q;
    for(int i = 1; i < n; i++){
        qn = qn * q;
    }

    printf(" u_%d=%f\n", n, u);
    printf(" u_%d=%f\n", n, qn);
    printf(" Difference=%f\n", u-qn);
}