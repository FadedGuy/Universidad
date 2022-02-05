#include <cstdio>

int get_spaces(int num){
    int sum = 0;
    while(num != 0){
        num /= 10;
        sum++;
    }
    return sum;
}

int main(){
    char op, c;
    int n_lines, n_col, i, j, spaces = 1;

    do{
        printf("operator: ");
        scanf(" %c", &op);
        while ((c = getchar()) != '\n' && c != EOF) { }
    }while(op != '+' && op != '-' && op != '*' && op != '/' && op != '%');

    do{
        printf("number of lines: ");
        scanf("%d", &n_lines);
        while ((c = getchar()) != '\n' && c != EOF) { }
    }while(n_lines <= 0);

    do{
        printf("number of columns: ");
        scanf("%d", &n_col);
        while ((c = getchar()) != '\n' && c != EOF) { }
    }while(n_col <= 0);

    switch (op){
    case '+':
        spaces += get_spaces((n_lines-1) + (n_col-1));
        break;
    case '-':
        spaces += get_spaces(n_col-1)+1;
        break;
    case '*':
        spaces += get_spaces((n_lines-1) * (n_col-1));
        break;
    case '/':
        spaces += get_spaces((n_lines-1));
        break;
    case '%':
        spaces += get_spaces(n_col-1);
        break;
    }

    printf("%-*c|", spaces-1, op);
    for(i = 0; i < n_col; i++){
        printf("%-*d", spaces, i);
    }
    printf("\n");

    printf("%*.*s", spaces, spaces, "----------------");
    for(i = 0; i < n_col; i++){
        printf("%*.*s", spaces, spaces, "----------------");
    }
    printf("\n");

    for(i = 0; i < n_lines; i++){
        for(j = -2; j < n_col; j++){
            if(j == -2){
                printf("%-*d", spaces-1, i);
            }
            else if(j == -1){
                printf("|");
            }
            else{
                if(j == 0 && op == '/'){
                    printf("%-*c", spaces-1, 'E');
                }
                else{
                    switch (op){
                        case '+':
                            printf("%-*d", spaces, (j+i));
                            break;
                        case '-':
                            printf("%-*d", spaces, (j-i));
                            break;
                        case '*':
                            printf("%-*d", spaces, (j*i));
                            break;
                        case '/':
                            printf("%-*d", spaces, (j/i));
                            break;
                        case '%':
                            printf("%-*d", spaces, (j%i));
                            break;
                    }
                }
            }
        }
        printf("\n");
    }

    return 0;
}