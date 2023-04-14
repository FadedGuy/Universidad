#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>

/*
    Prints formated 
    We could change it to accept an error code aswell
    Can also change to accept different streams, not only stderr
*/
void printError(const char* format, ...){
    va_list args;

    va_start(args, format);
    fprintf(stderr, "Error: ");
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    va_end(args);
}

/*
    Creates a TCP socket and binds it to the given port, if the 
    port is 0 then it assigns a random available port
*/
int createTCPSocket(int port){
    static struct sockaddr_in serverAddress;
    int sock;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1){
        printError("Unable to create TCP socket");
        return -1;
    }

    if(port == 0){
        return sock;
    }

    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    if(bind(sock, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1){
        printError("Unable to bind socket to port \"%d\"", port);
        close(sock);
        return -1;
    }

    return sock;
}
