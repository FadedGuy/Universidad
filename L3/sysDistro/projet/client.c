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

int createAvailableBeerRequest(int sock, requestPacket** packetPtr){
    char* payload = "0";
    *packetPtr = createRequestPacket(AVAILABLE_BEER, payload, strlen(payload));
    if(*packetPtr == NULL){
        return -1;
    }

    return 0;
}

int writeRequestPacket(int sock, requestPacket* packet){
    int totalSize = sizeof(requestType_t) + sizeof(size_t) + packet->payloadLength;
    int nbBytes;
    char* buffer = malloc(totalSize);
    
    if(buffer == NULL){
        printError("Unable to allocate \"%d\" bytes for request packet", totalSize);
        return -1;
    }

    memcpy(buffer, &(packet->requestType), sizeof(requestType_t));
    memcpy(buffer + sizeof(requestType_t), &(packet->payloadLength), sizeof(size_t));
    memcpy(buffer + sizeof(requestType_t) + sizeof(size_t), packet->payload, packet->payloadLength);

    nbBytes = send(sock, buffer, totalSize, 0);
    if(nbBytes == -1 || nbBytes != totalSize){
        printError("Error sending message to server: only %d/%d bytes were sent", nbBytes, totalSize);
        free(buffer);
        return -1;
    }

    free(buffer);
    return 0;
}

int readResponse(int sock, char** response, int* responseSize){
    int totalBytesRead = 0;
    int bytesRead = 0;
    char* buffer = malloc(BUFFER);

    if (buffer == NULL) {
        printf("Error: Unable to allocate memory for buffer\n");
        return -1;
    }

    while (1) {
        if (totalBytesRead + BUFFER + 1 > *responseSize) {
            int newResponseSize = *responseSize + BUFFER + 1;
            char* newResponse = realloc(*response, newResponseSize);
            if (newResponse == NULL) {
                printf("Error: Unable to allocate memory for response\n");
                free(buffer);
                return -1;
            }
            *response = newResponse;
            *responseSize = newResponseSize;
        }

        bytesRead = recv(sock, buffer, BUFFER, 0);
        if (bytesRead == -1) {
            printf("Error: Unable to receive data from server\n");
            free(buffer);
            return -1;
        }
        if (bytesRead == 0) {
            break;
        }

        memcpy(*response + totalBytesRead, buffer, bytesRead);
        totalBytesRead += bytesRead;
    }

    (*response)[totalBytesRead] = '\0';

    free(buffer);
    return 0;
}

int processRequest(requestType_t type, const int sock){
    requestPacket* packet;
    int statusCode;
    char* response = NULL;
    int responseSize = 0;

    switch(type){
        case AVAILABLE_BEER:
            statusCode = createAvailableBeerRequest(sock, &packet);
            break;
        case ORDER_BEER:
        default:
            printf("Yeah no!\n");
            statusCode = -1;
            break;
    };
    
    if(statusCode == -1){
        printError("Error creating request");
        freeRequestPacket(packet);
        return -1;
    }
    printf("Request has been created\n");

    statusCode = writeRequestPacket(sock, packet);
    if(statusCode == -1){
        printError("Error sending packet to server");
        freeRequestPacket(packet);
        return -1;
    }

    responseSize = BUFFER;
    response = malloc(responseSize);
    if(response == NULL){
        printError("Unable to allocate memory for response");
        freeRequestPacket(packet);
        return -1;
    }

    statusCode = readResponse(sock, &response, &responseSize);
    if(statusCode == -1){
        printError("Error reading packets from server");
        free(response);
        freeRequestPacket(packet);
        return -1;
    }
    printf("Response received from server: %s\n", response);

    free(response);
    freeRequestPacket(packet);
    return 0;
}

int main(int argc, char** argv){
    static struct sockaddr_in serverAddress;
    struct hostent* serverHostname;
    int sock;

    char* serverName;
    long serverPort;
    int statusCode;

    statusCode = parseArgInfo(argc, argv, &serverName, &serverPort);
    if(statusCode == -1){
        printError("Error while parsing arguments");
        exit(EXIT_FAILURE);
    }
    printf("Arguments parsed\n");

    sock = createTCPSocket(0);
    if(sock == -1){
        printError("Error while creating TCP Socket");
        exit(EXIT_FAILURE);
    }
    printf("Created TCP Socket\n");

    serverHostname = gethostbyname(serverName);
    if(serverHostname == NULL){
        printError("Error retrieving server IP for hostname \"%s\"", serverName);
        close(sock);
        exit(EXIT_FAILURE);
    }
    printf("Retrieved IP for hostname: \"%s\"\n", serverName);

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
    printf("Conencted to server!\n");

    statusCode = processRequest(AVAILABLE_BEER, sock);
    if(statusCode == -1){
        printError("Error processing request \"%d\"", AVAILABLE_BEER);
        close(sock);
        exit(EXIT_FAILURE);
    }
    printf("Processed request successfully!\n");
    
    close(sock);
    
    return EXIT_SUCCESS;
}   