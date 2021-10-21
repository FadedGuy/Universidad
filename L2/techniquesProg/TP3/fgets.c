#include <stdio.h>
#include <string.h>

#define BUF_SIZE 1000 /*Little trick*/

int main(int argc, char *argv[])
{
    FILE *file = NULL; 
    char buf[BUF_SIZE] = "aaaaaaa";
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

    fgets(buf, BUF_SIZE-1, file);
    if(ferror(file))
    {
        fprintf(stderr, "unable to read file\n");
        return 1;
    }
    printf("read: \"%s\" from %s\n", buf, argv[1]);

    ret = fclose(file);
    if(ret == EOF)
    {
        fprintf(stderr, "Unable to close file\n");
        return 1;
    }

    return 0;
}