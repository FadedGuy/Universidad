#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <semaphore.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "pipe.h"
#include "process.h"
#include "request.h"
#include "tap.h"
#include "util.h"

#define BUFFER 50
#define MAX_REQUESTS 5
#define NUM_PROC 2
#define QUANTUM 5
#define PIPE_MAIN_CLIENT "pipeMainClient"
#define PIPE_CLIENT_MAIN "pipeClientMain"

/*
    When pausing a process it doesn't really stop does it?
    Separate main process from main ?
    In controlProcess needs to send UDP with request for processus commande
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

// Needs to be modified accordingly for sem and tap
char* getAvailableBeerPayload(){
    int i;

    char* str = malloc(strlen("These are the available beers: ") + (sizeof(char)*(MAX_LENGTH_NAME*N_TAPS+1)) + 1);
    if(str == NULL){
        return NULL;
    }

    strcpy(str, "These are the available beers: "); 
    for(i = 0; i < N_TAPS; i++){
        strcat(str, getBeerName(i));
        
        if(i+1 < N_TAPS){
            strcat(str, ",");
        }
    }
    return str;
}

// It should be in the same order as beerPayload, check for the number that was given
char* getOrderBeerPayload(char* requestPayload){
    long chosenBeer, chosenSize;
    char* str;
    const char* p = requestPayload;
    char* end;

    chosenBeer = strtol(p, &end, 10);
    if(end == p || *end != ','){
        return NULL;
    }

    p = end + 1;
    chosenSize = strtol(p, &end, 10);
    if(end == p || *end != '\0'){
        return NULL;
    }

    if(chosenBeer < 1 && chosenBeer > N_TAPS){
        str = malloc(strlen("Invalid beer selection") + 1);
        if(str == NULL){
            return NULL;
        }
        strcpy(str, "Invalid beer selection");
    }
    else{
        // Order from pipe given beer
        printf("Ordered from tap %ld a %ld\n", chosenBeer, chosenSize);
        str = malloc(strlen("Here goes your beer") + 1);
        if(str == NULL){
            return NULL;
        }
        strcpy(str, "Here goes your beer");
    }

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

int clientCommunication(const int sock){
    int statusCode;
    char* responsePayload;
    requestPacket_t request;
    requestType_t responseType;
    pid_t pid = getpid();

    printf("A new client #%d has entered the bar!\n", pid);
    while(1){
        statusCode = readRequest(sock, &request);
        if(statusCode == -1){
            printError("Error receiving packet from client #%d", pid);
            return -1;
        }

        printf("Client on process #%d said: %s\n", pid, request.payload);

        // Process request
        switch(request.requestType){
            case C_AVAILABLE_BEER:
                responsePayload = getAvailableBeerPayload();
                responseType = S_AVAILABLE_BEER;
                break;
            case C_ORDER_BEER:
                responsePayload = getOrderBeerPayload(request.payload);
                responseType = S_ORDER_BEER;
                break;
            case C_EXIT_BAR:
                responsePayload = getExitBarPayload();
                responseType = S_EXIT_BAR;
                break;
            default:
                printError("Request type on client #%d: \"%d\" not recognised", pid, request.requestType);
                return -1;
        }

        if(responsePayload == NULL){
            printError("Error creating response payload for client# for \"%d\" type response", pid, responseType);
            return -1;
        }

        statusCode = sendRequest(responseType, sock, responsePayload, &request);
        if(statusCode == -1){
            printError("Error sending response to client# %d", pid);
            return -1;
        }
        printf("Reponse sent to client #%d\n", pid);
        
        free(responsePayload);

        if(request.requestType == C_EXIT_BAR){
            printf("Client #%d exited bar\n", pid);
            break;
        }

    }

    return 0;
}

void communicationProcess(va_list arguments){
    static struct sockaddr_in clientAddress;
    unsigned int lgAddress;
    int listeningSocket, serviceSocket;
    long localListeningPort;
    int statusCode;
    pid_t pidClient = getpid();

    int argc = va_arg(arguments, int);
    char** argv = va_arg(arguments, char**);

    statusCode = parseArgInfo(argc, argv, &localListeningPort);
    if(statusCode == -1){
        printError("Error while parsing arguments");
        exit(EXIT_FAILURE);
    }
    printf("Parsed args for communication process pid \"%d\"\n", pidClient);

    listeningSocket = createTCPSocket(localListeningPort);
    if(listeningSocket == -1){
        printError("Error while creating TCP socket");
        close(listeningSocket);
        exit(EXIT_FAILURE);
    }
    printf("Created TCP Socket - process pid \"%d\"\n", pidClient);

    statusCode = listen(listeningSocket, MAX_REQUESTS);
    if(statusCode == -1){
        printError("Error trying to listen for messages");
        close(listeningSocket);
        exit(EXIT_FAILURE);
    }
    printf("Listening for client requests - process pid \"%d\"\n", pidClient);

    while(1){
        lgAddress = sizeof(struct sockaddr_in);
        serviceSocket = accept(listeningSocket, (struct sockaddr*)&clientAddress, &lgAddress);
        if(serviceSocket == -1){
            printError("Error while accepting incoming connection from: \"%s\"", clientAddress.sin_addr.s_addr);
            exit(EXIT_FAILURE);
        }
        if((fork()) == 0){
            close(listeningSocket);
            statusCode = clientCommunication(serviceSocket);
            if(statusCode == -1){
                printError("Something went wrong with clientCommunication");
                exit(EXIT_FAILURE);
            }
            exit(EXIT_SUCCESS);
        }

        close(serviceSocket);
    }
    
    close(listeningSocket);
    exit(EXIT_SUCCESS);
}

void controlProcess(){
    tap_t* taps;
    sem_t* semaphore[N_TAPS];
    int shmid, statusCode, i, sock;
    char* response;

    sock = createUDPSocket(0);
    if(sock == -1){
        printError("Controle -> Unable to create UDP socket");
        exit(EXIT_FAILURE);
    }

    statusCode = exchangeUDPSocket(sock, "localhost", 7777, "bonjour from C", &response, BUFFER);
    if(statusCode == -1){
        printError("Controle -> Unable to send message via UDP socket");
        exit(EXIT_FAILURE);
    }
    printf("Got from server \"%s\"\n", response);


    shmid = retrieveTapSHM(SHM_KEY, N_TAPS);
    if(shmid == -1){
        printError("Controle: -> Error retrieving SHM");
        exit(EXIT_FAILURE);
    }
    printf("Controle: -> Retrieves Tap SHM\n");

    taps = attachTapSHM(shmid);
    if(taps == NULL){
        printError("Controle: -> Unable to attach to SHM");
        exit(EXIT_FAILURE);
    }
    printf("Controle: -> Attach Tap SHM\n");
    
    statusCode = openTapSemaphore(semaphore, N_TAPS, SEM_KEY);
    if(statusCode == -1){
        printError("Controle: -> Error opening semaphore");
        exit(EXIT_FAILURE);
    }
    printf("Controle: -> Opened Tap semaphore\n");

    printf("Controle -> Keg's are being now monitored\n");
    while(statusCode == 0){

        for(i = 0; i < N_TAPS; i++){
            statusCode = checkKeg(semaphore[i], &taps[i], i);
            if(statusCode == -1){
                printError("Error checking keg %d", i);
            }
        }
        sleep(2);
    }
    printf("Controle -> Keg's are no longer being monitored\n");

    
    if(detachTapSHM(taps) == -1){
        printError("Controle: -> Error detaching from tap");
        exit(EXIT_FAILURE);
    }

    if(closeTapSemaphore(semaphore, N_TAPS) == -1){
        printError("Controle: -> Error closing semaphores");
        exit(EXIT_FAILURE);
    }


    exit(EXIT_SUCCESS);
}

int main(int argc, char** argv){
    tap_t* taps;
    sem_t* semaphore[N_TAPS];
    int shmid, statusCode; 
    
    pid_t pidProcesses[NUM_PROC];
    int currentPidIndex;

    if(createPipe(PIPE_MAIN_CLIENT) == -1){
        printError("Unable to create pipe named %s", PIPE_MAIN_CLIENT);
        exit(EXIT_FAILURE);
    }

    if(createPipe(PIPE_CLIENT_MAIN) == -1){
        printError("Unable to create pipe named %s", PIPE_CLIENT_MAIN);
        exit(EXIT_FAILURE);
    }

    // SHM w semaphore 
    shmid = retrieveTapSHM(SHM_KEY, N_TAPS);
    if(shmid == -1){
        printError("Error retrieving SHM");
        exit(EXIT_FAILURE);
    }
    printf("Retrieve tap SHM\n");

    taps = attachTapSHM(shmid);
    if(taps == NULL){
        printError("Unable to attach to SHM");
        exit(EXIT_FAILURE);
    }
    printf("Attach tap SHM\n");
    
    statusCode = openTapSemaphore(semaphore, N_TAPS, SEM_KEY);
    if(statusCode == -1){
        printError("Error opening semaphore");
        exit(EXIT_FAILURE);
    }
    printf("Opened sem for tap\n");
    
    // Communication
    pidProcesses[0] = launchNewProcess("Communication", &communicationProcess, argc, argv);
    if(pidProcesses[0] == -1){
        printError("Error launching communication process");
        exit(EXIT_FAILURE);
    }

    // Controle
    pidProcesses[1] = launchNewProcess("Control", &controlProcess);
    if(pidProcesses[1] == -1){
        printError("Error launching control process");
        exit(EXIT_FAILURE);
    }

    sleep(2);
    currentPidIndex = 0;
    while(1){
        printf("Continuing with pid %d\n", pidProcesses[currentPidIndex]);
        kill(pidProcesses[currentPidIndex], SIGCONT);

        sleep(QUANTUM);

        printf("Stopping pid %d\n", pidProcesses[currentPidIndex]);
        kill(pidProcesses[currentPidIndex], SIGSTOP);


        if(checkProcessStatus(pidProcesses, NUM_PROC) == -1){
            printError("Checking the health of processes failed");
            terminateAll(pidProcesses, NUM_PROC);
            break;
        } else{
            currentPidIndex = getNextProcessIndex(currentPidIndex, NUM_PROC);
        }
    }

    terminateAll(pidProcesses, NUM_PROC);
    
    if(detachTapSHM(taps) == -1){
        printError("Error detaching tap");
        exit(EXIT_FAILURE);
    }

    if(closeTapSemaphore(semaphore, N_TAPS) == -1){
        printError("Error closing semaphore");
        exit(EXIT_FAILURE);
    }
    
    

    return EXIT_SUCCESS;
}