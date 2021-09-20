#include <stdio.h>
#include <math.h>

int main()
{
    float c, d;
    int n = 1000;
    printf("Donne c: ");
    scanf("%f", &c);
    printf("Donne d: ");
    scanf("%f", &d);

    float an = 0, bn = 0, a = an;
    for(int i = 1; i <=n; i++){
        an = (an*an) - (bn*bn) + c; 
        bn = (2*a*bn) + d;
        a = an;
    }

    printf("res: %f\n", sqrt((an*an) + (bn*bn)));
}