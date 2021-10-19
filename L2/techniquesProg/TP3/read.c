#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 10

int main(int argc, char *argv[])
{
    int fd = -1;
    int nBytes = -1;

    if(argc != 2)
    {
        fprintf(stderr, "invalid number of arguments\n");
        return 1;
    }

    fd = open(argv[1], O_RDONLY);
    if(fd == -1)
    {
        fprintf(stderr, "unable to open file\n");
        return 1;
    }

    

    return 0;
}