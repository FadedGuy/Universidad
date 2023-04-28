#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "utils/logger.h"
#include "utils/request.h"
#include "utils/util.h"

#define BUFFER 50

/**
 * Parses the information given when the program was ran
 * @param nbArgs Number of arguments given
 * @param args Arguments given
 * @param name Server address name
 * @param port Server port
 * @return 0 on success, -1 for errors
*/
int parseArgInfo(int nbArgs, char** args, char** name, long* port){
    char *end;
    
    if(nbArgs != 3){
        logError("Incorrect usage. Use ./client server_adress server_port");
        return -1;
    }

    *name = args[1];
    if(*name == NULL){
        logErrorWithArgs("Unable to parse server name: \"%s\"", args[1]);
        return -1;
    }

    *port = strtol(args[2], &end, 10);
    if(args[2] == end || errno == ERANGE){
        logErrorWithArgs("Unable to parse server port: \"%s\"", args[2]);
        return -1;
    }

    return 0;
}

/**
 * Prompts the user for an integer and checks if it's within range
 * @param prompt Text user will see
 * @param upper Choice upper limit inclusive
 * @param lower Choice lower limit inclusive
 * @return Choice on success, -1 if error
*/
long getMenuChoice(const char* prompt, const long lower, const long upper){
    char input[1024];
    char* endptr;    
    int success;
    long choice;

    do{
        printf("%s", prompt);
        if(!fgets(input, 1024, stdin)){
            logError("Reading input failed");
            return -1;
        }

        // Convert string to long int
        endptr = NULL;
        choice = strtol(input, &endptr, 10);
        errno = 0;
        if(errno == ERANGE){
            logError("Number is outside of long range");
            continue;
        } else if(endptr == input){
            logError("No characters were read");
            success = 0;
        } else if(*endptr && *endptr != '\n'){
            logError("Unable to convert all input");
            success = 0;
        } else if(choice < lower || choice > upper){
            logErrorWithArgs("Choice is not within menu range of %d-%d", lower, upper);
            success = 0;
        } else{
            success = 1;
        }

    }while(!success);

    return choice;
}

char* getAvailableBeerPayload(){
    char* str = malloc(strlen(EMPTY_PAYLOAD) + 1);
    if(str == NULL){
        logError("Unable to allocate memory");
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
    
    choicePint = getMenuChoice("Pint(1) or Half-Pint(2): ", 1, 2);
    snprintf(choicePintStr, BUFFER, "%ld", choicePint);

    str = malloc(strlen(choiceBeerStr) + strlen(choicePintStr) + 2);
    if(str == NULL){
        logError("Unable to allocate memory");
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
        logError("Unable to allocate memory");
        return NULL;
    }

    strcpy(str, "Goodbye"); 

    return str;
}

int clientMenu(const int sock){
    int statusCode;
    long choice;
    char* requestPayload;
    RequestPacket* response;

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
                break;
            case C_EXIT_BAR:
                requestPayload = getExitBarPayload();
                break;
            default:
                logErrorWithArgs("Choice \"%ld\" is not known", choice);
                return -1;
        }

        if(requestPayload == NULL){
            logErrorWithArgs("Unable to generate payload for request \"%d\"", choice);
            return -1;
        }

        response = mallocRequest();
        if(response == NULL){
            logError("Unable to allocate memory for response");
            return -1;
        }

        statusCode = sendRequest(choice, sock, requestPayload, response);
        if(statusCode == -1){
            logErrorWithArgs("Unable to process request \"%d\"", choice);
            freeRequestPacket(response);
            return -1;
        }
        printf("Server said: %s\n", getRequestPayload(response));

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
        logError("Error while parsing arguments");
        exit(EXIT_FAILURE);
    }

    sock = createTCPSocket(0);
    if(sock == -1){
        logError("Error while creating TCP Socket");
        close(sock);
        exit(EXIT_FAILURE);
    }

    statusCode = connectToTCPSocket(sock, serverName, serverPort);
    if(statusCode == -1){
        logError("Error while connecting to socket");
        close(sock);
        exit(EXIT_FAILURE);
    }


    statusCode = clientMenu(sock);
    if(statusCode == -1){
        logError("Error while client was at the bar");
        close(sock);
        exit(EXIT_FAILURE);
    }
    printf("You've exited successfully!\n");
    
    close(sock);
    
    return EXIT_SUCCESS;
}   
