#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#include "logger.h"
#include "request.h"

struct requestPacket_t{
    RequestType   requestType;
    size_t        payloadLength;
    char*         payload;
};

RequestPacket* createRequestPacket(const RequestType type, const char* payload, const size_t payloadSize){
    RequestPacket* packet = malloc(sizeof(RequestPacket));
    if(packet == NULL){
        logError("Error allocating memory for packet");
        return NULL;
    }

    packet->requestType = type;
    packet->payload = malloc(payloadSize);
    if(packet->payload == NULL){
        logError("Error allocating memory for payload in packet");
        return NULL;
    }
    packet->payloadLength = payloadSize;
    memcpy(packet->payload, payload, payloadSize);

    return packet;
}

RequestPacket* mallocRequest(){
    RequestPacket* request;

    request = malloc(sizeof *request);
    return request;
}

void freeRequestPacket(RequestPacket* packet){
    if(packet == NULL){
        return;
    }

    free(packet->payload);
    free(packet);
}

int writeRequest(const int sock, const RequestPacket* packet){
    int totalSize = sizeof(RequestType) + sizeof(size_t) + packet->payloadLength;
    int nbBytes;
    char* buffer = malloc(totalSize);
    
    if(buffer == NULL){
        logErrorWithArgs("Unable to allocate \"%d\" bytes for request packet", totalSize);
        return -1;
    }

    memcpy(buffer, &(packet->requestType), sizeof(RequestType));
    memcpy(buffer + sizeof(RequestType), &(packet->payloadLength), sizeof(size_t));
    memcpy(buffer + sizeof(RequestType) + sizeof(size_t), packet->payload, packet->payloadLength);

    nbBytes = send(sock, buffer, totalSize, 0);
    if(nbBytes == -1 || nbBytes != totalSize){
        logErrorWithArgs("Error sending message to server: only %d/%d bytes were sent", nbBytes, totalSize);
        free(buffer);
        return -1;
    }

    free(buffer);
    return 0;
}

int readRequest(const int sock, RequestPacket* packet){
    int nbBytes;

    nbBytes = recv(sock, &(packet->requestType), sizeof(RequestType), 0);
    if(nbBytes != sizeof(RequestType)){
        logError("requestType error");
        return -1;
    }

    nbBytes = recv(sock, &(packet->payloadLength), sizeof(size_t), 0);
    if(nbBytes != sizeof(size_t)){
        logError("payloadLength error");
        return -1;
    }

    packet->payload = malloc(packet->payloadLength + 1);
    if(packet->payload == NULL){
        logError("Unable to allocate for payload");
        return -1;
    }

    nbBytes = recv(sock, packet->payload, packet->payloadLength, 0);
    if(nbBytes != packet->payloadLength){
        logError("payload error");
        return -1;
    }

    packet->payload[packet->payloadLength] = '\0';
    return 0;
}

int sendRequest(const RequestType type, const int sock, const char* payload, RequestPacket* response){
    RequestPacket* packet;
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
            logErrorWithArgs("Request type given not recognised: \"%d\"", type);
            statusCode = -1;
            break;
    };
    
    if(packet == NULL){
        logError("Error creating request");
        return -1;
    }

    statusCode = writeRequest(sock, packet);
    if(statusCode == -1){
        logError("Error sending packet");
        return -1;
    }

    if(type >= CLIENT_LOWER && type <= CLIENT_UPPER){
        // Client request type
        statusCode = readRequest(sock, response);
        if(statusCode == -1){
            logError("Error reading packets from server");
            return -1;
        }
    } 

    freeRequestPacket(packet);
    return 0;
}

char* getRequestPayload(const RequestPacket* request){
    return request->payload;
}

RequestType getRequestType(const RequestPacket* request){
    return request->requestType;
}

