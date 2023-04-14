#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <signal.h>
#include <string.h>

#include "util.h"

#define BUFFER 50

/*
    We could add support for SIGINT or any other for when the program closes
    so it properly cleans up
*/

int parseArgInfo(int nbArgs, char** args, char** name, long* port){
    char *end;
    
    if(nbArgs != 3){
        printError("Incorrect usage. Use ./client server_adress server_port");
        return -1;
    }

    *name = args[1];
    if(*name == NULL){
        printError("Unable to parse server name: \"%s\"", args[1]);
        return -1;
    }

    *port = strtol(args[2], &end, 10);
    if(args[2] == end || errno == ERANGE){
        printError("Unable to parse server port: \"%s\"", args[2]);
        return -1;
    }

    return 0;
}


int main(int argc, char** argv){
    static struct sockaddr_in serverAddress;
    struct hostent* serverHostname;
    int sock;

    char* serverName;
    long serverPort;

    int statusCode;

    char* message = "Hi there";
    char response[BUFFER];
    int nbBytes;


    statusCode = parseArgInfo(argc, argv, &serverName, &serverPort);
    if(statusCode == -1){
        printError("Error while parsing arguments");
        exit(EXIT_FAILURE);
    }

    sock = createTCPSocket(0);
    if(sock == -1){
        printError("Error while creating TCP Socket");
        exit(EXIT_FAILURE);
    }

    serverHostname = gethostbyname(serverName);
    if(serverHostname == NULL){
        printError("Error retrieving server IP for hostname \"%s\"", serverName);
        close(sock);
        exit(EXIT_FAILURE);
    }

    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(serverPort);
    memcpy(&serverAddress.sin_addr.s_addr, serverHostname->h_addr_list[0], serverHostname->h_length);
    statusCode = connect(sock, (struct sockaddr*)&serverAddress, sizeof(struct sockaddr_in));
    if(statusCode == -1){
        printError("Error connecting to server");
        close(sock);
        exit(EXIT_FAILURE);
    }


    nbBytes = write(sock, message, strlen(message)+1);
    if(nbBytes == -1 || nbBytes != strlen(message)+1){
        printError("Error sending message to server: only %d/%d bytes were sent", nbBytes, strlen(message)+1);
        close(sock);
        exit(EXIT_FAILURE);
    } 

    nbBytes = read(sock, response, BUFFER);
    if(nbBytes == -1){
        printError("Error receiving message from server, ERRNO=%d", errno);
        close(sock);
        exit(EXIT_FAILURE);
    } else if(nbBytes == 0){
        printf("Reached EOF\n");
    }

    printf("Response with %d bytes: %s\n", nbBytes, response);

    close(sock);
    
    return EXIT_SUCCESS;
}   