#include <stdio.h>

#define BUF_SIZE 10

int main(int argc, char *argv[])
{
    FILE *file = NULL; 
    int nItems = -1;
    char buf[BUF_SIZE] = "";
    int ret = EOF;

    if(argc != 2)
    {
        fprintf(stderr, "invalid number of arguments\n");
        return 1;
    }

    file = fopen(argv[1], "r");
    if(file == NULL)
    {
        fprintf(stderr, "unable to open file\n");
        return 1;
    }

    while(nItems != 0)
    {
        nItems = fread(buf, sizeof(char),BUF_SIZE-1, file);
        if(ferror(file))
        {
            fprintf(stderr, "unable to read file\n");
            return 1;
        }
        buf[nItems] = '\0';
        printf("read: \"%s\" (%d byte(s) from %s)\n", buf, nItems, argv[1]);
    }

    ret = fclose(file);
    if(ret == EOF)
    {
        fprintf(stderr, "Unable to close file\n");
        return 1;
    }

    return 0;
}