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
#define MAX_REQUESTS 5

int parseArgInfo(int argc, char** argv, long* port){
    char *end;

    if(argc != 2){
        printError("Incorrect usage. Use: %s listeningPort", argv[0]);
        return -1;
    }

    *port = strtol(argv[1], &end, 10);
    if(argv[1] == end || errno == ERANGE){
        printError("Unable to parse server port: \"%s\"", argv[1]);
        return -1;
    }

    return 0;
}

int communications(int sock){
    int statusCode;
    char* response;
    requestPacket request;

    while(1){
        statusCode = readClientRequest(sock, &request);
        if(statusCode == -1){
            printError("Error receiving packet from client #%d", sock);
            return -1;
        }

        printf("Client #%d said: %s\n", sock, request.payload);

        // Process request
        switch(request.requestType){
            case AVAILABLE_BEER:
                response = malloc(strlen("These are available:")+1);
                strcpy(response, "These are available:");
                break;
            case ORDER_BEER:
                response = malloc(strlen("Here u go")+1);
                strcpy(response, "Here u go");
                break;
            case EXIT_BAR:
                response = malloc(strlen("Come back later!")+1);
                strcpy(response, "Come back later!");
                break;
            default:
                printError("Request type \"%d\" not recognised", request.requestType);
        }


        statusCode = writeClientResponse(sock, response);
        if(statusCode == -1){
            printError("Error sending response to client");
            return -1;
        }
        printf("Reponse sent to client #%d\n", sock);
        
        if(request.requestType == EXIT_BAR){
            printf("Client #%d exited bar\n", sock);
            return 0;
        }
    }

    return 0;
}

int main(int argc, char** argv){
    static struct sockaddr_in clientAddress;
    unsigned int lgAddress;
    int listeningSocket, serviceSocket;
    long localListeningPort;

    int statusCode;

    statusCode = parseArgInfo(argc, argv, &localListeningPort);
    if(statusCode == -1){
        printError("Error while parsing arguments");
        exit(EXIT_FAILURE);
    }

    listeningSocket = createTCPSocket(localListeningPort);
    if(listeningSocket == -1){
        printError("Error while creating TCP socket");
        close(listeningSocket);
        exit(EXIT_FAILURE);
    }

    statusCode = listen(listeningSocket, MAX_REQUESTS);
    if(statusCode == -1){
        printError("Error trying to listen for messages");
        close(listeningSocket);
        exit(EXIT_FAILURE);
    }

    while(1){
        lgAddress = sizeof(struct sockaddr_in);
        serviceSocket = accept(listeningSocket, (struct sockaddr*)&clientAddress, &lgAddress);
        if(serviceSocket == -1){
            printError("Error while accepting incoming connection from: \"%s\"", clientAddress.sin_addr.s_addr);
            exit(EXIT_FAILURE);
        }
        if(fork() == 0){
            close(listeningSocket);
            communications(serviceSocket);
            exit(EXIT_SUCCESS);
        }

        close(serviceSocket);
    }
    
    close(listeningSocket);

    return EXIT_SUCCESS;
}