#ifndef UTIL
#define UTIL

#define CLEAR_TERMINAL printf("\033[2J\033[1;1H");
#define PROVIDER_SEND_PORT 7777
#define PROVIDER_RECEIVE_PORT 7778
#define BUFFER 50

/**
 * Creates a TCP socket
 * @param port Binds socket to port if it's other than 0
 * @return Socket on success, -1 otherwise
*/
int createTCPSocket(int port);

/**
 * Creates a UDP socket
 * @param port Binds socket to port it if it's not 0
 * @return Socket on success, -1 otherwise
*/
int createUDPSocket(int port);

/**
 * Connects client's socket to the with given server name and port
 * @param sock Socket to be connected
 * @param serverName Name to search for host IP
 * @param serverPort Port of the server to connect
 * @return 0 on success, -1 for errors
*/
int connectToTCPSocket(const int sock, const char* serverName, const long serverPort);

/**
 * Sends and receives a message from a UDP socket 
 * @param sock Socket to connect
 * @param serverName Name to search for host IP
 * @param serverPort Port of the server to connect
 * @param localPort Port to listen for server response
 * @param msg Message to send
 * @param response Where the response will be stored
 * @return 0 on success, -1 for errors
*/
int exchangeUDPSocket(const int sock, const char* serverName, const long serverPort, const long localPort, const char* msg, char* response);


#endif