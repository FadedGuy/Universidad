#include <stdlib.h>
#include <string.h>

#include "request.h"

requestPacket* createRequestPacket(requestType_t type, char* payload, size_t size){
    requestPacket* packet = malloc(sizeof(requestPacket));
    packet->requestType = type;
    packet->payload = malloc(size);
    packet->payloadLength = size;
    memcpy(packet->payload, payload, size);

    return packet;
}

void freeRequestPacket(requestPacket* packet){
    if(packet == NULL){
        return;
    }

    free(packet->payload);
    free(packet);
}