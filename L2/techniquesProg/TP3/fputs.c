#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *file = NULL;
    int ret = EOF;
    
    if(argc != 3)
    {
        fprintf(stderr, "invalid number of arguments\n");
        return 1;
    }

    file = fopen(argv[1], "w");
    if(file == NULL)
    {
        fprintf(stderr, "Unable to open the file\n");        
        return 1;
    }

    fputs(argv[2], file);
    if(ferror(file))
    {
        fprintf(stderr, "Unable to write to file\n");        
        return 1;        
    }

    printf("written: \"%s\" to \"%s\"\n", argv[2], argv[1]);

    ret = fclose(file);
    if(ret == EOF)
    {
        fprintf(stderr, "Unable to close file\n");
        return 1;
    }

    return 0;
}