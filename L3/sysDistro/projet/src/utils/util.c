#include <errno.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "logger.h"
#include "util.h"

int createTCPSocket(int port){
    static struct sockaddr_in serverAddress;
    int sock;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1){
        logError("Unable to create TCP socket");
        return -1;
    }

    if(port == 0){
        return sock;
    }

    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    if(bind(sock, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1){
        logErrorWithArgs("Unable to bind socket to port \"%d\"", port);
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
        logError("Unable to create UDP socket");
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
        logErrorWithArgs("Unable to bind socket to port \"%d\"%s", port, strerror(errno));
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
        logErrorWithArgs("Error retrieving server IP for hostname \"%s\"", serverName);
        return -1;
    }

    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(serverPort);
    memcpy(&serverAddress.sin_addr.s_addr, serverHostname->h_addr_list[0], serverHostname->h_length);
    if(connect(sock, (struct sockaddr*)&serverAddress, sizeof(struct sockaddr_in)) == -1){
        logError("Error connecting to server");
        return -1;
    }

    return 0;
}

int exchangeUDPSocket(const int sock, const char* serverName, const long serverPort, const long localPort, const char* msg, char* response){
    static struct sockaddr_in serverAddress;
    struct hostent* serverHostname;
    unsigned int lg;
    int nbBytes;
    char* buffer = malloc(sizeof(char)*50);
    int newSock;

    serverHostname = gethostbyname(serverName);
    if(serverHostname == NULL){
        logErrorWithArgs("Error retrieving server IP for hostname \"%s\"", serverName);
        return -1;
    }
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(serverPort);
    
    lg = sizeof(struct sockaddr_in);
    nbBytes = sendto(sock, msg, strlen(msg)+1, 0, (struct sockaddr*)&serverAddress, lg);
    if(nbBytes == -1){
        logErrorWithArgs("Error sending message to %d", sock);
        return -1;
    }

    newSock = createUDPSocket(localPort);
    if(newSock == -1){
        logErrorWithArgs("Error creating receiving socket on port %d", localPort);
    }

    nbBytes = recvfrom(newSock, buffer, BUFFER, 0, NULL, &lg);
    if(nbBytes == -1){
        logError("Error receiving message");
        return -1;
    }

    strncpy(response, buffer, nbBytes);
    close(sock);
    close(newSock);

    return 0;
}