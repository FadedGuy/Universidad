#ifndef REQUEST
#define REQUEST

#define BUFFER 50

typedef enum {
    AVAILABLE_BEER,
    ORDER_BEER,
} requestType_t;

typedef struct{
    requestType_t requestType;
    size_t payloadLength;
    char* payload;
} requestPacket;

/**
 * Returns a packet type containing it's type, payload and payload's size
 * @param type Request type
 * @param payload Payload to be set in the request
 * @param payloadSize Payload size
 * @return Packet on sucess, NULL otherwise
*/
requestPacket* createRequestPacket(const requestType_t type, const char* payload, const size_t payloadSize);

/**
 * Frees all memory allocated in packet
 * @param packet Packet to be freed
*/
void freeRequestPacket(requestPacket* packet);

/**
 * Send the packet to the socket
 * @param sock Socket to which the packet will be sent to
 * @param packet Packet to be sent
 * @return 0 on sucess, -1 for errors
*/
int writeClientRequestPacket(const int sock, const requestPacket* packet);

/**
 * Reads response sent by the server
 * @param sock Socket from which to read data
 * @param response Where the response will be saved
 * @param responseSize Where the size of the response will be saved
 * @return 0 on sucess, -1 for errors
*/
int readServerResponse(const int sock, char** response, int* responseSize);

/**
 * Sends a packet to the given socket
 * @param type Type of request packet to be sent
 * @param sock Socket to whihc packet will be sent 
 * @return 0 on sucess, -1 for errors
*/
int sendRequest(const requestType_t type, const int sock, const char* payload);

#endif