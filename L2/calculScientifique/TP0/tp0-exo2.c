#include <stdio.h>
#include <math.h>

//a 2>1000 = a >1001 + b 2>1000 - c
//b 2>1000 = a 2>1000 - a >1001 + c

//b >1001 = (2 * a >1000 * b >1000) + d
// 
//sqrt(a 2>1000 + b 2>1000)
//sqrt(a > 1001 + b 2>1000 - c  +  a 2>1000 - a >1001 + c)
//c nímporte pas?
//sqrt((a > 1001 * 2) + b 2>1000 + a 2>1000)

//b 1 = 2 * 0 * 0 + d
//b 1 = d

//b 2 = 2 * 
int main()
{
    float c, d;
    int n = 1000;
    printf("Donne c: ");
    scanf("%f", &c);
    printf("Donne d: ");
    scanf("%f", &d);

    float an = 0, bn = 0;
    for(int i = 1; i <=n; i++){
        an = (an*an) - (bn*bn) + c; 
        bn = (2*an*bn) + d;
    }

    printf("res: %f\n", sqrt((an*an) + (bn*bn)));
}