#ifndef UTIL
#define UTIL

#define CLEAR_TERMINAL printf("\033[2J\033[1;1H");

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
 * Connects client's socket to the server name and port given
 * @param sock Socket to be connected
 * @param serverName Name to search for host IP
 * @param serverPort Port of the server to connect
 * @return 0 on sucess, -1 for errors
*/
int connectToSocket(const int sock, const char* serverName, const long serverPort);


#endif