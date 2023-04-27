#include <errno.h>
#include <limits.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "utils/logger.h"
#include "utils/request.h"
#include "utils/util.h"

#define BUFFER 50

/**
 * Parses the information given when the program was ran
 * @param nbArgs number of arguments given
 * @param args arguments given
 * @param name server address name
 * @param port server port
 * @return 0 on sucess, -1 for errors
*/
int parseArgInfo(int nbArgs, char** args, char** name, long* port){
    char *end;
    
    if(nbArgs != 3){
        logError(stderr, "parseArgInfo", "Incorrect usage. Use ./client server_adress server_port");
        return -1;
    }

    *name = args[1];
    if(*name == NULL){
        logError(stderr, "parseArgInfo", "Unable to parse server name: \"%s\"", args[1]);
        return -1;
    }

    *port = strtol(args[2], &end, 10);
    if(args[2] == end || errno == ERANGE){
        logError(stderr, "parseArgInfo", "Unable to parse server port: \"%s\"", args[2]);
        return -1;
    }

    return 0;
}

/**
 * Prompts the user for an integer and checks it's within range
 * @param prompt Text user will see
 * @param upper Choice upper limit inclusive
 * @param lower Choice lower limit inclusive
 * @return Choice on sucess, -1 if error
*/
long getMenuChoice(const char* prompt, const long lower, const long upper){
    char input[1024];
    char* endptr;    
    int sucess;
    long choice;

    do{
        printf("%s", prompt);
        if(!fgets(input, 1024, stdin)){
            logError(stderr, "getMenuChoice", "Reading input failed");
            return -1;
        }

        endptr = NULL;
        errno = 0;
        choice = strtol(input, &endptr, 10);
        if(errno == ERANGE){
            logError(stderr, "getMenuChoice", "Number is outside of long range");
            continue;
        } else if(endptr == input){
            logError(stderr, "getMenuChoice", "No characters were read");
            sucess = 0;
        } else if(*endptr && *endptr != '\n'){
            logError(stderr, "getMenuChoice", "Unable to convert all input");
            sucess = 0;
        } else if(choice < lower || choice > upper){
            logError(stderr, "getMenuChoice", "Choice is not within menu range of %d-%d", lower, upper);
            sucess = 0;
        } else{
            sucess = 1;
        }

    }while(!sucess);

    return choice;
}

char* getAvailableBeerPayload(){
    char* str = malloc(strlen(EMPTY_PAYLOAD) + 1);
    if(str == NULL){
        logError(stderr, "getAvailableBeerPayload", "Unable to allocate memory");
        return NULL;
    }

    strcpy(str, EMPTY_PAYLOAD); 
    return str;
}

char* getOrderBeerPayload(){
    long choiceBeer, choicePint;
    char choiceBeerStr[BUFFER], choicePintStr[BUFFER];
    char* str;

    choiceBeer = getMenuChoice("What beer do you want to order? Enter a positive number: ", 1, LONG_MAX);
    snprintf(choiceBeerStr, BUFFER, "%ld", choiceBeer);
    
    // Change from pint or half-pint? There are more options?
    choicePint = getMenuChoice("Pint(1) or Half-Pint(2): ", 1, 2);
    snprintf(choicePintStr, BUFFER, "%ld", choicePint);

    str = malloc(strlen(choiceBeerStr) + strlen(choicePintStr) + 2);
    if(str == NULL){
        logError(stderr, "getOrderBeerPayload", "Unable to allocate memory");
        return NULL;
    }

    strcpy(str, choiceBeerStr); 
    strcat(str, ","); 
    strcat(str, choicePintStr);

    return str;
}

char* getExitBarPayload(){
    char* str = malloc(strlen("Goodbye") + 1);
    if(str == NULL){
        logError(stderr, "getExitBarPayload", "Unable to allocate memory");
        return NULL;
    }

    strcpy(str, "Goodbye"); 
    return str;
}

int clientMenu(const int sock){
    int statusCode;
    long choice;
    char* requestPayload;
    requestPacket_t* response;


    while(1){
        printf("-------------------------\n\tMENU\n");
        printf("Choose an option:\n");
        printf("1. Show available beers\n");
        printf("2. Order a beer\n");
        printf("3. Exit\n");

        choice = getMenuChoice("Enter your choice: ", CLIENT_LOWER, CLIENT_UPPER);
        switch(choice){
            case C_AVAILABLE_BEER:
                requestPayload = getAvailableBeerPayload();
                break;
            case C_ORDER_BEER:
                requestPayload = getOrderBeerPayload();
                logInfo(stdout, "clientMenu", "Your beer is on the way");
                break;
            case C_EXIT_BAR:
                requestPayload = getExitBarPayload();
                break;
            default:
                logError(stderr, "clientMenu", "Choice \"%ld\" is not known", choice);
                return -1;
        }

        if(requestPayload == NULL){
            logError(stderr, "clientMenu", "Unable to generate payload for request \"%d\"", choice);
            return -1;
        }

        response = malloc(sizeof *response);
        if(response == NULL){
            logError(stderr, "clientMenu", "Unable to allocate memory for response");
            return -1;
        }

        statusCode = sendRequest(choice, sock, requestPayload, response);
        if(statusCode == -1){
            logError(stderr, "clientMenu", "Unable to process request \"%d\"", choice);
            freeRequestPacket(response);
            return -1;
        }
        logInfo(stdout, "clientMenu", "Server said: %s\n", response->payload);

        freeRequestPacket(response);
        free(requestPayload);        
        if(choice == 3){
            return 0;
        }
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
        logError(stderr, "main", "Error while parsing arguments");
        exit(EXIT_FAILURE);
    }

    sock = createTCPSocket(0);
    if(sock == -1){
        logError(stderr, "main", "Error while creating TCP Socket");
        close(sock);
        exit(EXIT_FAILURE);
    }

    statusCode = connectToTCPSocket(sock, serverName, serverPort);
    if(statusCode == -1){
        logError(stderr, "main", "Error while connecting to socket");
        close(sock);
        exit(EXIT_FAILURE);
    }


    statusCode = clientMenu(sock);
    if(statusCode == -1){
        logError(stderr, "main", "Error while client was at the bar");
        close(sock);
        exit(EXIT_FAILURE);
    }
    logInfo(stdout, "menu", "Client exited successfully!");
    

    close(sock);
    return EXIT_SUCCESS;
}   
