#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>

#include "util.h"
#include "logger.h"

int createTCPSocket(int port){
    static struct sockaddr_in serverAddress;
    int sock;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1){
        logError(stderr,  "createTCPSocket", "Unable to create TCP socket");
        return -1;
    }

    if(port == 0){
        return sock;
    }

    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    if(bind(sock, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1){
        logError(stderr,  "createTCPSocket", "Unable to bind socket to port \"%d\"", port);
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
        logError(stderr,  "createUDPSocket", "Unable to create UDP socket");
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
        logError(stderr,  "createUDPSocket", "Unable to bind socket to port \"%d\"%s", port, strerror(errno));
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
        logError(stderr,  "connectToTCPSocket", "Error retrieving server IP for hostname \"%s\"", serverName);
        return -1;
    }

    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(serverPort);
    memcpy(&serverAddress.sin_addr.s_addr, serverHostname->h_addr_list[0], serverHostname->h_length);
    if(connect(sock, (struct sockaddr*)&serverAddress, sizeof(struct sockaddr_in)) == -1){
        logError(stderr,  "connectToTCPSocket", "Error connecting to server");
        return -1;
    }

    return 0;
}

int exchangeUDPSocket(const int sock, const char* serverName, const long serverPort, const long localPort, const char* msg, char** response, const int responseSize){
    static struct sockaddr_in serverAddress;
    struct hostent* serverHostname;
    unsigned int lg;
    int nbBytes;
    char* buffer = malloc(sizeof(char)*50);
    int newSock;


    serverHostname = gethostbyname(serverName);
    if(serverHostname == NULL){
        logError(stderr,  "exchangeUDPSocket", "Error retrieving server IP for hostname \"%s\"", serverName);
        return -1;
    }
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(serverPort);
    
    lg = sizeof(struct sockaddr_in);
    nbBytes = sendto(sock, msg, strlen(msg)+1, 0, (struct sockaddr*)&serverAddress, lg);
    if(nbBytes == -1){
        logError(stderr,  "exchangeUDPSocket", "Error sending message to %d", sock);
        return -1;
    }
    logDebug(stdout, "exchangeUDPSocket", "Message sent!");

    // serverHostname = gethostbyname("localhost");
    // if(serverHostname == NULL){
    //     logError(stderr,  "exchangeUDPSocket", "Error retrieving server IP for hostname \"%s\"", "localhost");
    //     return -1;
    // }
    // memset(&serverAddress, 0, sizeof(serverAddress));
    // serverAddress.sin_family = AF_INET;
    // serverAddress.sin_port = htons(localPort);
    // newSock = createUDPSocket(0);
    newSock = createUDPSocket(7778);
    logInfo(stdout, "exchangeUDPSocket", "created UDP Socket");

    nbBytes = 0;
    while(1) {
        nbBytes = recvfrom(newSock, buffer, responseSize, 0, NULL, &lg);
        if(nbBytes == -1){
            logError(stderr,  "exchangeUDPSocket", "Error receiving message");
            return -1;
        }
        logDebug(stdout, "exchangeUDPSocket", "Received %d bytes from socket", nbBytes);
    }
    

    response = malloc(nbBytes*sizeof(char));
    if(response == NULL){
        logError(stderr,  "exchangeUDPSocket", "Unable to allocate memory");
        return -1;
    }
    memcpy(response, buffer, nbBytes);

    close(sock);

    return 0;
}