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

int writeRequest(const int sock, const requestPacket* packet){
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

int readRequest(const int sock, requestPacket* packet){
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

int sendRequest(const requestType_t type, const int sock, const char* payload, requestPacket* response){
    requestPacket* packet;
    int statusCode;

    switch(type){
        case C_AVAILABLE_BEER:
        case C_ORDER_BEER:
        case C_EXIT_BAR:
        case S_AVAILABLE_BEER:
        case S_ORDER_BEER:
        case S_EXIT_BAR:
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

    statusCode = writeRequest(sock, packet);
    if(statusCode == -1){
        printError("Error sending packet");
        freeRequestPacket(packet);
        return -1;
    }

    if(type >= CLIENT_LOWER && type <= CLIENT_UPPER){
        // Client request type
        statusCode = readRequest(sock, response);
        if(statusCode == -1){
            printError("Error reading packets from server");
            freeRequestPacket(packet);
            return -1;
        }
    } 

    freeRequestPacket(packet);
    return 0;
}


