#include <stdio.h>

int main()
{
    unsigned long billet;
    long banknotes[] = {0,0,0,0,0,0,0};

    do
    {
        printf("banknote: ");
        scanf("%lu", &billet);
        while(getchar() != '\n');

        switch(billet)
        {
            case -1:
                fprintf(stderr, "exit\n");
                return 0;


            case 5:
                banknotes[0]++;
                break;
            case 10:
                banknotes[1]++;
                break;
            case 20:
                banknotes[2]++;
                break;
            case 50:
                banknotes[3]++;
                break;
            case 100:
                banknotes[4]++;
                break;
            case 200:
                banknotes[5]++;
                break;
            case 500:
                banknotes[6]++;
                break;
            
            default:
                fprintf(stderr, "invalid banknote value\n");
                break;

        }

        printf("%ld banknote(s) of 5 euros \n", banknotes[0]);
        printf("%ld banknote(s) of 10 euros \n", banknotes[1]);
        printf("%ld banknote(s) of 20 euros \n", banknotes[2]);
        printf("%ld banknote(s) of 50 euros \n", banknotes[3]);
        printf("%ld banknote(s) of 100 euros \n", banknotes[4]);
        printf("%ld banknote(s) of 200 euros \n", banknotes[5]);
        printf("%ld banknote(s) of 500 euros \n", banknotes[6]);

    }while(billet != -1);

    return 0;
}