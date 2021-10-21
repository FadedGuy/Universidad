#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    /*2 parametres + chemin program execute 3*/
    int fd = -1;
    int ret = -1;
    int nBytes = -1;
    
    if(argc != 3)
    {
        fprintf(stderr, "invalid number of arguments\n");
        return 1;
    }

    fd = open(argv[1], O_WRONLY | O_CREAT | O_APPEND, 0700);
    if(fd == -1)
    {
        fprintf(stderr, "Unable to open the file\n");        
        return 1;
    }

    nBytes = write(fd, argv[2], strlen(argv[2]));
    write(fd, "\n", 1); /*Saut de ligne, on peut enregistrer si on veux nBytes*/
    if(nBytes == -1)
    {
        fprintf(stderr, "Unable to write to file\n");
        return 1;
    }

    printf("written: \"%s\" (%d byte(s) to \"%s\")\n", argv[2], nBytes, argv[1]);

    ret = close(fd);
    if(ret == -1)
    {
        fprintf(stderr, "Unable to close file\n");
        return 1;
    }
    
    return 0;
}