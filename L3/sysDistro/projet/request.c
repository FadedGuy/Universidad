#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#include "util.h"
#include "request.h"

requestPacket* createRequestPacket(const requestType_t type, const char* payload, const size_t payloadSize){
    requestPacket* packet = malloc(sizeof(requestPacket));
    if(packet == NULL){
        printError("Error allocating memory for packet");
        return NULL;
    }

    packet->requestType = type;
    packet->payload = malloc(payloadSize);
    if(packet->payload == NULL){
        printError("Error allocating memory for payload in packet");
        return NULL;
    }
    packet->payloadLength = payloadSize;
    memcpy(packet->payload, payload, payloadSize);

    return packet;
}

void freeRequestPacket(requestPacket* packet){
    if(packet == NULL){
        return;
    }

    free(packet->payload);
    free(packet);
}

int writeServerRequest(const int sock, const requestPacket* packet){
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

int readServerResponse(const int sock, char** response, int* responseSize){
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

        if (totalBytesRead >= strlen(END_RESPONSE)-1 && strcmp(*response + totalBytesRead - strlen(END_RESPONSE)-1, END_RESPONSE) == 0) {
            break;
        }   
    }

    (*response)[totalBytesRead] = '\0';

    free(buffer);
    return 0;
}

int sendRequest(const requestType_t type, const int sock, const char* payload){
    requestPacket* packet;
    int statusCode;
    char* response = NULL;
    int responseSize = 0;

    switch(type){
        case AVAILABLE_BEER:
        case ORDER_BEER:
        case EXIT_BAR:
            packet = createRequestPacket(type, payload, strlen(payload));
            break;
        default:
            printError("Request type given not recognised: \"%d\"", type);
            statusCode = -1;
            break;
    };
    
    if(packet == NULL){
        printError("Error creating request");
        return -1;
    }

    statusCode = writeServerRequest(sock, packet);
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
    
    statusCode = readServerResponse(sock, &response, &responseSize);
    if(statusCode == -1){
        printError("Error reading packets from server");
        free(response);
        freeRequestPacket(packet);
        return -1;
    }
    printf("Response received from server: %s\n", response);

    if(response !=  NULL){
        free(response);
    }
    freeRequestPacket(packet);
    return 0;
}

int writeClientResponse(const int sock, const char* response){
    int nbBytes;

    nbBytes = send(sock, response, strlen(response)+1, 0);
    if(nbBytes == -1 || nbBytes != strlen(response)+1){
        printError("Error sending message to client: only %d/%d bytes were sent", nbBytes, strlen(response)+1);
        return -1;
    }    

    nbBytes = send(sock, END_RESPONSE, strlen(END_RESPONSE)+1, 0);
    if(nbBytes == -1 || nbBytes != strlen(END_RESPONSE)+1){
        printError("Error sending end message to client: only %d/%d bytes were sent", nbBytes, strlen(END_RESPONSE)+1);
        return -1;
    } 

    return 0;
}

int readClientRequest(const int sock, requestPacket* packet){
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

