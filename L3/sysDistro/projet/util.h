#ifndef UTIL
#define UTIL

#define CLEAR_TERMINAL printf("\033[2J\033[1;1H");

/*
    Expand print error to print normal per process?
*/

/**
 * Prints formatted errors
 * @param format String that will be printed with the format
 * @param ... Arguments to be used in the formatting
*/
void printError(const char* format, ...);

/**
 * Creates a TCP socket
 * @param port Binds socket to port if it's other than 0
 * @return Socket on sucess, -1 otherwise
*/
int createTCPSocket(int port);

/**
 * Creates a UDP socket
 * @param port Binds socket to port it if it's not 0
 * @return Socket on sucess,-1 otherwise
*/
int createUDPSocket(int port);

/**
 * Connects client's socket to the server name and port given
 * @param sock Socket to be connected
 * @param serverName Name to search for host IP
 * @param serverPort Port of the server to connect
 * @return 0 on sucess, -1 for errors
*/
int connectToTCPSocket(const int sock, const char* serverName, const long serverPort);

/**
 * Sends and receives a message from a UDP socket 
 * @param sock Socket to connect
 * @param serverName Name to search for host IP
 * @param serverPort Port of the server to connect
 * @param msg Message to send
 * @param response Where the response will be stored
 * @param responseSize Max size of the response buffer
 * @return 0 on sucess, -1 for errors
*/
int exchangeUDPSocket(const int sock, const char* serverName, const long serverPort, const char* msg, char** response, const int responseSize);


#endif