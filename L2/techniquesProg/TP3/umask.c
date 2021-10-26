#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *file = NULL;
    int ret = EOF;
    char *pEnd;
    long decimal = 0, binary = 0, i = 1;

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

    printf("Old umask = %#o\n", umask());
    
    // uMaskCal = ((6-((argv[2][0]-'0')))*100) + ((6-((argv[2][1]-'0')))*10) + (6-((argv[2][2]-'0'))); 
    // printf("%d\n", uMaskCal);
    umask(uMaskCal);

    file = fopen(argv[1], "w");
    if(file == NULL)
    {
        fprintf(stderr, "Unable to open the file\n");        
        return 1;
    }

    ret = fclose(file);
    if(ret == EOF)
    {
        fprintf(stderr, "Unable to close file\n");
        return 1;
    }

    printf("New umask = %#o\n", umask());
    
    return 0;
}