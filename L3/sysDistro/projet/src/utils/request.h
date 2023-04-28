#ifndef REQUEST
#define REQUEST

#define BUFFER 50
#define EMPTY_PAYLOAD "0"

#define CLIENT_LOWER C_AVAILABLE_BEER
#define CLIENT_UPPER C_EXIT_BAR
#define SERVER_LOWER S_AVAILABLE_BEER
#define SERVER_UPPER S_EXIT_BAR

typedef enum requestType_t{
    C_AVAILABLE_BEER = 1,
    C_ORDER_BEER,
    C_EXIT_BAR,
    S_AVAILABLE_BEER,
    S_ORDER_BEER,
    S_EXIT_BAR,
} RequestType;

typedef struct requestPacket_t RequestPacket;

/**
 * Returns a packet type containing it's type, payload and payload's size
 * @param type Request type
 * @param payload Payload to be set in the request
 * @param payloadSize Payload size
 * @return Packet on sucess, NULL otherwise
*/
RequestPacket* createRequestPacket(const RequestType type, const char* payload, const size_t payloadSize);

/**
 * Attemps to allocate memory for a request packet
 * @return Pointer on sucess, NULL otherwise
*/
RequestPacket* mallocRequest();

/**
 * Frees all memory allocated in packet
 * @param packet Packet to be freed
*/
void freeRequestPacket(RequestPacket* packet);

/**
 * Send a packet to the socket
 * @param sock Socket to which the packet will be sent to
 * @param packet Packet to be sent
 * @return 0 on sucess, -1 for errors
*/
int writeRequest(const int sock, const RequestPacket* packet);

/**
 * Reads the incoming packet from socket
 * @param sock Socket where data is received
 * @param packet Packet where data will be stored
 * @return 0 on sucess, -1 for errors
*/
int readRequest(const int sock, RequestPacket* packet);

/**
 * Sends a packet to the given socket
 * @param type Type of request packet to be sent
 * @param sock Socket to which packet will be sent 
 * @return 0 on sucess, -1 for errors
*/
int sendRequest(const RequestType type, const int sock, const char* payload, RequestPacket* response);

/**
 * Getter for the payload in a RequestPacket
 * @param request RequestPacket to get payload
 * @return Payload from request
*/
char* getRequestPayload(const RequestPacket* request);

RequestType getRequestType(const RequestPacket* request);


#endif