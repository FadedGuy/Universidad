#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *file = NULL;
    int ret = EOF;
    int nItems = -1;
    
    if(argc != 3)
    {
        fprintf(stderr, "invalid number of arguments\n");
        return 1;
    }

    file = fopen(argv[1], "a");
    if(file == NULL)
    {
        fprintf(stderr, "Unable to open the file\n");        
        return 1;
    }

    nItems = fwrite(argv[2], sizeof(char), strlen(argv[2]),file);
    if(ferror(file))
    {
        fprintf(stderr, "Unable to write to file\n");        
        return 1;        
    }

    printf("written: \"%s\" (%d byte(s) to \"%s\")\n", argv[2], nItems, argv[1]);

    ret = fclose(file);
    if(ret == EOF)
    {
        fprintf(stderr, "Unable to close file\n");
        return 1;
    }

    return 0;
}