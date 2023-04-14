#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>

#include "util.h"

#define BUFFER 50
#define MAX_REQUESTS 5

int parseArgInfo(int argc, char** argv, long* port){
    char *end;

    if(argc != 2){
        printError("Incorrect usage. Use: %s listeningPort", argv[0]);
        return -1;
    }

    *port = strtol(argv[1], &end, 10);
    if(argv[1] == end || errno == ERANGE){
        printError("Unable to parse server port: \"%s\"", argv[1]);
        return -1;
    }

    return 0;
}

int communications(int sock){
    int nbBytes;
    char* message = NULL;
    char response[] = "Hi there client";

    message = malloc(sizeof(char)*BUFFER);
    if(message == NULL){
        printError("Unable to allocate more memory");
        return -1;
    }

    nbBytes = read(sock, message, BUFFER);
    if(nbBytes == -1){
        printError("Error receiving message from client, ERRNO=%d", errno);
        return -1;
    } else if(nbBytes == 0){
        printf("Reached EOF\n");
    }
    printf("Received %d bytes: %s\n", nbBytes, message);

    nbBytes = write(sock, response, strlen(response)+1);
    if(nbBytes == -1 || nbBytes != strlen(response)+1){
        printError("Error sending message to client: only %d/%d bytes were sent", nbBytes, strlen(response)+1);
        return -1;
    } 

    return 0;
}

int main(int argc, char** argv){
    static struct sockaddr_in clientAddress;
    unsigned int lgAddress;
    int listeningSocket, serviceSocket;
    long localListeningPort;

    int statusCode;

    statusCode = parseArgInfo(argc, argv, &localListeningPort);
    if(statusCode == -1){
        printError("Error while parsing arguments");
        exit(EXIT_FAILURE);
    }

    listeningSocket = createTCPSocket(localListeningPort);
    if(listeningSocket == -1){
        printError("Error while creating TCP socket");
        close(listeningSocket);
        exit(EXIT_FAILURE);
    }

    statusCode = listen(listeningSocket, MAX_REQUESTS);
    if(statusCode == -1){
        printError("Error trying to listen for messages");
        close(listeningSocket);
        exit(EXIT_FAILURE);
    }

    while(1){
        lgAddress = sizeof(struct sockaddr_in);
        serviceSocket = accept(listeningSocket, (struct sockaddr*)&clientAddress, &lgAddress);
        if(serviceSocket == -1){
            printError("Error while accepting incoming connection from: \"%s\"", clientAddress.sin_addr.s_addr);
            exit(EXIT_FAILURE);
        }
        if(fork() == 0){
            close(listeningSocket);
            communications(serviceSocket);
            exit(EXIT_SUCCESS);
        }

        close(serviceSocket);
    }
    
    close(listeningSocket);

    return EXIT_SUCCESS;
}