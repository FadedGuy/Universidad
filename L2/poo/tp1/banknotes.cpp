#include <cstdio>

int main(){
    int banknotes[7] = {0,0,0,0,0,0,0};
    int opc;
    int c;

    do{
        printf("banknote: ");
        scanf("%d", &opc);
        while ((c = getchar()) != '\n' && c != EOF) { }

        switch (opc)
        {
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

        printf("%d banknote(s) of 5 euros\n", banknotes[0]);
        printf("%d banknote(s) of 10 euros\n", banknotes[1]);
        printf("%d banknote(s) of 20 euros\n", banknotes[2]);
        printf("%d banknote(s) of 50 euros\n", banknotes[3]);
        printf("%d banknote(s) of 100 euros\n", banknotes[4]);
        printf("%d banknote(s) of 200 euros\n", banknotes[5]);
        printf("%d banknote(s) of 500 euros\n", banknotes[6]);

    }while(opc != -1);

    printf("exit\n");

    return 0;
}