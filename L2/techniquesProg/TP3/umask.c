#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *file = NULL;
    int ret = EOF;
    mode_t msk;

    if(argc != 3)
    {
        fprintf(stderr, "invalid number of arguments\n");
        return 1;
    }

    if(!((argv[2][0] >= '0' && argv[2][0] <= '7') && (argv[2][1] >= '0' && argv[2][1] <= '7') && (argv[2][2] >= '0' && argv[2][2] <= '7')))
    {
        fprintf(stderr, "invalid umask\n");
        return 1;
    }
    msk = strtol(argv[2], NULL, 8);
    printf("%d\n", msk);

    file = fopen(argv[1], "w");
    if(file == NULL)
    {
        fprintf(stderr, "Unable to open the file\n");        
        return 1;
    }

    ret = fclose(file);
    if(ret == EOF)
    {
        fprintf(stderr, "unable to close file\n");
        return 1;
    }

    return 0;
}