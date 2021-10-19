#include <stdio.h>
#include <string.h>

void mirror(char *str, char *res)
{
    int i = 0;
    int j = strlen(str)-1;
    while(i < strlen(str))
    {
        res[i] = str[j];
        i++;
        j--;
    }
    res[i] = '\0';
}

int main(int argc, char *argv[])
{
    char res[11];
    if(argc != 2)
    {
        fprintf(stderr, "invalid number of arguments\n");
        return 1;
    }
    if(strlen(argv[1]) > 10)
    {
        fprintf(stderr, "the string length is greater than 10\n");
        return 1;
    }
    mirror(argv[1], res);
    /*printf("\"%s\"\n", res);*/
    fprintf(stdin,"\"%s\"\n", res);
    return 0;
}