#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>

#include "util.h"
#include "request.h"

#define BUFFER 50

/*
    We could add support for SIGINT or any other for when the program closes
    so it properly cleans up
*/

/**
 * Parses the information given when the program was ran
 * @param nbArgs number of arguments given
 * @param args arguments given
 * @param name server address name
 * @param port server port
*/
int parseArgInfo(int nbArgs, char** args, char** name, long* port){
    char *end;
    
    if(nbArgs != 3){
        printError("Incorrect usage. Use ./client server_adress server_port");
        return -1;
    }

    *name = args[1];
    if(*name == NULL){
        printError("Unable to parse server name: \"%s\"", args[1]);
        return -1;
    }

    *port = strtol(args[2], &end, 10);
    if(args[2] == end || errno == ERANGE){
        printError("Unable to parse server port: \"%s\"", args[2]);
        return -1;
    }

    return 0;
}

int clientMenu(const int sock){
    int statusCode;
    
    statusCode = sendRequest(AVAILABLE_BEER, sock, "0");
    if(statusCode == -1){
        printError("Error processing request \"%d\"", AVAILABLE_BEER);
        return -1;
    }

    return 0;
}

int main(int argc, char** argv){
    int sock;
    int statusCode;
    long serverPort;
    char* serverName;

    statusCode = parseArgInfo(argc, argv, &serverName, &serverPort);
    if(statusCode == -1){
        printError("Error while parsing arguments");
        exit(EXIT_FAILURE);
    }
    printf("Arguments parsed\n");

    sock = createTCPSocket(0);
    if(sock == -1){
        printError("Error while creating TCP Socket");
        close(sock);
        exit(EXIT_FAILURE);
    }
    printf("Created TCP Socket\n");

    statusCode = connectToSocket(sock, serverName, serverPort);
    if(statusCode == -1){
        printError("Error while connecting to socket");
        close(sock);
        exit(EXIT_FAILURE);
    }
    printf("Conencted to socket!\n");


    statusCode = clientMenu(sock);
    if(statusCode == -1){
        printError("Error while client was at the bar");
        close(sock);
        exit(EXIT_FAILURE);
    }
    printf("Client exited successfully!\n");
    
    close(sock);
    
    return EXIT_SUCCESS;
}   