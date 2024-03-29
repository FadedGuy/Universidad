#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 10

int main(int argc, char *argv[])
{
    int fd = -1;
    int nBytes = -1;
    char buf[BUF_SIZE];
    int ret = -1;

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

    while(nBytes != 0)
    {
        nBytes = read(fd, buf, BUF_SIZE-1);
        if(nBytes == -1)
        {
            fprintf(stderr, "unable to read file\n");
            return 1;
        }
        buf[nBytes] = '\0';
        printf("read: \"%s\" (%d byte(s) from %s)\n", buf, nBytes, argv[1]);
    }

    ret = close(fd);
    if(ret == -1)
    {
        fprintf(stderr, "Unable to close file\n");
        return 1;
    }

    return 0;
}