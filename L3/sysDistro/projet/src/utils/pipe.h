#ifndef PIPE
#define PIPE

/**
 * Creates a pipe with name, if one with name exists, it first deletes it
 * @param name Name of the pipe
 * @return 0 on success, -1 for errors
*/
int createPipe(const char* name);

/**
 * Send a message through a named pipe
 * @param name Name of the pipe
 * @param message Message to send
 * @param messageSize Size of the message
 * @return 0 on success, -1 for errors
*/
int sendPipe(const char* name, const char* message, const int messageSize);

/**
 * Receives a message from a named pipe
 * @param name Name of the pipe
 * @param buffer Buffer where message will be stored
 * @param bufferSize Max size of a message that can be received
 * @return nbBytes received on success, -1 for errors
*/
int receivePipe(const char* name, char* buffer, int bufferSize);

#endif