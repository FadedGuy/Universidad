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
#include "tap.h"

#define BUFFER 50
#define MAX_REQUESTS 5

/*
    Struct named process for ordennanceur
    In main create the different processes
    SHM for two taps one of each, array protected by semaphore
    Response to client:
        available beer: comma separated beer types from array of taps (check for quantity)
        order beer: wait for turn, "serve", substract from given tap & return response if successful serve
        exit bar: NA
*/

/**
 * Parses the information given when the program was ran
 * @param argc number of arguments given
 * @param argv arguments given
 * @param port server port to open and listen
 * @return 0 on sucess, -1 for errors
*/
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

char* getAvailableBeerPayload(){
    char* str = malloc(strlen("These are the available beers we have here") + 1);
    if(str == NULL){
        return NULL;
    }

    strcpy(str, "These are the available beers we have here"); 
    return str;
}

char* getOrderBeerPayload(){
    char* str = malloc(strlen("Here u go client, one beer") + 1);
    if(str == NULL){
        return NULL;
    }

    strcpy(str, "Here u go client, one beer"); 
    return str;
}

char* getExitBarPayload(){
    char* str = malloc(strlen("Come back afterwards!") + 1);
    if(str == NULL){
        return NULL;
    }

    strcpy(str, "Come back afterwards!"); 
    return str;
}

int communications(int sock){
    int statusCode;
    char* responsePayload;
    requestPacket_t request;
    requestType_t responseType;

    while(1){
        statusCode = readRequest(sock, &request);
        if(statusCode == -1){
            printError("Error receiving packet from client #%d", sock);
            return -1;
        }

        printf("Client #%d said: %s\n", sock, request.payload);

        // Process request
        switch(request.requestType){
            case C_AVAILABLE_BEER:
                responsePayload = getAvailableBeerPayload();
                responseType = S_AVAILABLE_BEER;
                break;
            case C_ORDER_BEER:
                responsePayload = getOrderBeerPayload();
                responseType = S_ORDER_BEER;
                break;
            case C_EXIT_BAR:
                responsePayload = getExitBarPayload();
                responseType = S_EXIT_BAR;
                break;
            default:
                printError("Request type \"%d\" not recognised", request.requestType);
                return -1;
        }

        if(responsePayload == NULL){
            printError("Error create response payload for \"%d\" type", responseType);
            return -1;
        }

        statusCode = sendRequest(responseType, sock, responsePayload, &request);
        if(statusCode == -1){
            printError("Error sending response to client");
            return -1;
        }
        printf("Reponse sent to client #%d\n", sock);
        
        if(request.requestType == C_EXIT_BAR){
            printf("Client #%d exited bar\n", sock);
            return 0;
        }

        free(responsePayload);
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