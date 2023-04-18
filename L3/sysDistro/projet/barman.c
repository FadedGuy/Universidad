#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>

#include "util.h"
#include "request.h"
#include "tap.h"
#include "process.h"

#define BUFFER 50
#define MAX_REQUESTS 5
#define NUM_PROC 2
#define QUANTUM 5

/*
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

int clientCommunication(const int sock){
    int statusCode;
    char* responsePayload;
    requestPacket_t request;
    requestType_t responseType;
    pid_t pid = getpid();

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
                responsePayload = getOrderBeerPayload();
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

int communicationProcess(int argc, char** argv){
    static struct sockaddr_in clientAddress;
    unsigned int lgAddress;
    int listeningSocket, serviceSocket;
    long localListeningPort;
    int statusCode;
    pid_t pidClient = getpid();

    printf("%d\n", pidClient);

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

int main(int argc, char** argv){
    tap_t* taps;
    sem_t* semaphore[N_TAPS];
    int shmid, statusCode, i, iter;
    
    pid_t pidProcesses[NUM_PROC];
    int currentPidIndex;

    // SHM w semaphore 
    shmid = initSHM(SHM_KEY, N_TAPS, &taps);
    if(shmid == -1){
        printError("Error initializing SHM");
        exit(EXIT_FAILURE);
    }

    statusCode = openTapSemaphore(semaphore, N_TAPS, SEM_KEY);
    if(statusCode == -1){
        printError("Error opening semaphore");
        exit(EXIT_FAILURE);
    }
    printf("Opened sem\n");

    for(i = 0; i < N_TAPS; i++){
        statusCode = initializeTap(semaphore[i], &taps[i], i+1);
        if(statusCode == -1){
            printError("Error initializing tap \"%d\" with type \"%d\"", 0, i+1);
            exit(EXIT_FAILURE);
        }
        printf("Tap %d initialized\n", i);
    }
    printf("Taps initialized\n");
    

    pidProcesses[0] = fork();
    if(pidProcesses[0] == -1){
        printError("Unable to create communication process");
        exit(EXIT_FAILURE);
    } else if(pidProcesses[0] == 0){
        printf("Initializing communication process\n");
        communicationProcess(argc, argv);
    }

    pidProcesses[1] = fork();
    if (pidProcesses[1] == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pidProcesses[1] == 0) {
        iter = 0;
        while (iter < 5) {
            printf("-----Child process 2 running\n");
            iter++;
            sleep(1);
        }
        exit(EXIT_SUCCESS);
    }

    currentPidIndex = 0;
    while(1){
        printf("Continuing with pid %d\n", pidProcesses[currentPidIndex]);
        kill(pidProcesses[currentPidIndex], SIGCONT);

        sleep(QUANTUM);

        printf("Stopping pid %d\n", pidProcesses[currentPidIndex]);
        kill(pidProcesses[currentPidIndex], SIGSTOP);


        if(checkProcessStatus(pidProcesses, NUM_PROC) == -1){
            printError("Checking the health of processes failed");
            break;
        } else{
            currentPidIndex = getNextProcessIndex(currentPidIndex, NUM_PROC);
        }
    }
    
    if(detachTapSHM(taps) == -1){
        printError("Error detaching tap");
        exit(EXIT_FAILURE);
    }

    if(closeTapSemaphore(semaphore, N_TAPS) == -1){
        printError("Error closing semaphore");
        exit(EXIT_FAILURE);
    }
    
    removeTapSHM(shmid);

    return EXIT_SUCCESS;
}