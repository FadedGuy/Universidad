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
#include "request.h"

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

int receivePacket(int sock, requestPacket* packet){
    int nbBytes;

    nbBytes = recv(sock, &(packet->requestType), sizeof(requestType_t), 0);
    if(nbBytes != sizeof(requestType_t)){
        printError("requestType error");
        return -1;
    }

    nbBytes = recv(sock, &(packet->payloadLength), sizeof(size_t), 0);
    if(nbBytes != sizeof(size_t)){
        printError("payloadLength error");
        return -1;
    }

    packet->payload = malloc(packet->payloadLength + 1);
    if(packet->payload == NULL){
        printError("Unable to allocate for payload");
        return -1;
    }

    nbBytes = recv(sock, packet->payload, packet->payloadLength, 0);
    if(nbBytes != packet->payloadLength){
        printError("payload error");
        free(packet->payload);
        return -1;
    }

    packet->payload[packet->payloadLength] = '\0';

    return 0;
}

int communications(int sock){
    int nbBytes;
    int statusCode;
    char response[] = "Hi there client";
    requestPacket request;

    statusCode = receivePacket(sock, &request);
    if(statusCode == -1){
        printError("Error receiving packet from client");
        return -1;
    }

    printf("Client said: %d %s\n", request.requestType, request.payload);

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