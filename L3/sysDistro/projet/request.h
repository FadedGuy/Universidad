#ifndef REQUEST
#define REQUEST

typedef enum {
    AVAILABLE_BEER,
    ORDER_BEER,
} requestType_t;

typedef struct{
    requestType_t requestType;
    size_t payloadLength;
    char* payload;
} requestPacket;

requestPacket* createRequestPacket(requestType_t type, char* payload, size_t size);

void freeRequestPacket(requestPacket* packet);

#endif