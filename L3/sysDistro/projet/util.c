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

#include "util.h"

void printError(const char* format, ...){
    va_list args;

    va_start(args, format);
    fprintf(stderr, "Error: ");
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    va_end(args);
}

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

int createUDPSocket(int port){
    static struct sockaddr_in serverAddress;
    int sock;

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock == -1){
        printError("Unable to create UDP socket");
        return -1;
    }

    if(port == 0){
        return sock;
    }

    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(sock, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1){
        printError("Unable to bind socket to port \"%d\"", port);
        close(sock);
        return -1;
    }

    return sock;

}

int connectToTCPSocket(const int sock, const char* serverName, const long serverPort){
    static struct sockaddr_in serverAddress;
    struct hostent* serverHostname;

    serverHostname = gethostbyname(serverName);
    if(serverHostname == NULL){
        printError("Error retrieving server IP for hostname \"%s\"", serverName);
        return -1;
    }

    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(serverPort);
    memcpy(&serverAddress.sin_addr.s_addr, serverHostname->h_addr_list[0], serverHostname->h_length);
    if(connect(sock, (struct sockaddr*)&serverAddress, sizeof(struct sockaddr_in)) == -1){
        printError("Error connecting to server");
        return -1;
    }

    return 0;
}

int exchangeUDPSocket(const int sock, const char* serverName, const long serverPort, const char* msg, char** response, const int responseSize){
    static struct sockaddr_in serverAddress;
    struct hostent* serverHostname;
    unsigned int lg;
    int nbBytes;
    char buffer[responseSize];

    serverHostname = gethostbyname(serverName);
    if(serverHostname == NULL){
        printError("Error retrieving server IP for hostname \"%s\"", serverName);
        return -1;
    }

    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(serverPort);
    memcpy(&serverAddress.sin_addr.s_addr, serverHostname->h_addr_list[0], serverHostname->h_length);
    
    lg = sizeof(struct sockaddr_in);
    nbBytes = sendto(sock, msg, strlen(msg)+1, 0, (struct sockaddr*)&serverAddress, lg);
    if(nbBytes == -1){
        printError("Error sending message to %d", sock);
        return -1;
    }
    printf("Message sent\n");

    nbBytes = recvfrom(sock, buffer, responseSize, 0, (struct sockaddr*)&serverAddress, &lg);
    if(nbBytes == -1){
        printError("Error receiving message");
        return -1;
    }

    response = malloc(nbBytes*sizeof(char));
    memcpy(response, buffer, nbBytes);

    close(sock);

    return 0;
}