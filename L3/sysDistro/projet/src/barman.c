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

#include "utils/pipe.h"
#include "utils/process.h"
#include "utils/request.h"
#include "utils/tap.h"
#include "utils/util.h"
#include "utils/logger.h"

#define BUFFER 50
#define MAX_REQUESTS 5
#define NUM_PROC 3
#define QUANTUM 10
#define PIPE_MAIN_CLIENT "/tmp/pipeMainClient"
#define PIPE_CLIENT_MAIN "/tmp/pipeClientMain"

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
        logError(stderr, "parseArgInfo", "Incorrect usage. Use: %s listeningPort", argv[0]);
        return -1;
    }

    *port = strtol(argv[1], &end, 10);
    if(argv[1] == end || errno == ERANGE){
        logError(stderr, "parseArgInfo", "Unable to parse server port: \"%s\"", argv[1]);
        return -1;
    }

    return 0;
}

char* getAvailableBeerPayload(requestPacket_t request){
    int type = (int)request.requestType;
    char* buffer = malloc(sizeof(char)*BUFFER);
    
    if(buffer == NULL){
        logError(stderr, "getAvailableBeerPayload", "Unable to allocate memory for buffer");
        return NULL;
    }

    sprintf(buffer, "%d", type);
    if(sendPipe(PIPE_CLIENT_MAIN, buffer, sizeof(char)*strlen(buffer) + 1) == -1){
        logError(stderr, "getAvailableBeerPayload", "Error sending message to pipe %s", PIPE_CLIENT_MAIN);
        return NULL;
    }

    if(receivePipe(PIPE_MAIN_CLIENT, buffer, BUFFER) == -1){
        logError(stderr, "getAvailableBeerPayload", "Error receiving message from pipe %s", PIPE_MAIN_CLIENT);
        return NULL;
    }

    return buffer;
}

char* getOrderBeerPayload(requestPacket_t request){
    int type = (int)request.requestType;
    char* buffer = malloc(sizeof(char)*BUFFER);

    if(buffer == NULL){
        logError(stderr, "getOrderBeerPayload", "Unable to allocate memory for buffer");
        return NULL;
    }

    sprintf(buffer, "%d", type);
    strcat(buffer, " ");
    strcat(buffer, request.payload);
    if(sendPipe(PIPE_CLIENT_MAIN, buffer, sizeof(char)*strlen(buffer) + 1) == -1){
        logError(stderr, "getOrderBeerPayload", "Error sending message to pipe %s", PIPE_CLIENT_MAIN);
        return NULL;
    }

    if(receivePipe(PIPE_MAIN_CLIENT, buffer, BUFFER) == -1){
        logError(stderr, "getOrderBeerPayload", "Error receiving message from pipe %s", PIPE_MAIN_CLIENT);
        return NULL;
    }

    return buffer;
}

char* getExitBarPayload(){
    char* str = malloc(strlen("Come back afterwards!") + 1);
    if(str == NULL){
        logError(stderr, "getExitBarPayload", "Unable to allocate memory for buffer");
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

    logInfo(stdout, "clientCommunication", "A new client #%d has entered the bar!", pid);
    while(1){
        statusCode = readRequest(sock, &request);
        if(statusCode == -1){
            logError(stderr, "clientCommunication", "Error receiving packet from client #%d", pid);
            return -1;
        }

        logInfo(stdout, "clientCommunication", "Client on process #%d said: %s\n", pid, request.payload);
        // Process request
        switch(request.requestType){
            case C_AVAILABLE_BEER:
                responsePayload = getAvailableBeerPayload(request);
                responseType = S_AVAILABLE_BEER;
                break;
            case C_ORDER_BEER:
                responsePayload = getOrderBeerPayload(request);
                responseType = S_ORDER_BEER;
                break;
            case C_EXIT_BAR:
                responsePayload = getExitBarPayload();
                responseType = S_EXIT_BAR;
                break;
            default:
                logError(stderr, "clientCommunication", "Request type on client #%d: \"%d\" not recognised", pid, request.requestType);
                return -1;
        }

        if(responsePayload == NULL){
            logError(stderr, "clientCommunication", "Error creating response payload for client# for \"%d\" type response", pid, responseType);
            return -1;
        }

        statusCode = sendRequest(responseType, sock, responsePayload, &request);
        if(statusCode == -1){
            logError(stderr, "clientCommunication", "Error sending response to client# %d", pid);
            return -1;
        }
        logInfo(stdout, "clientCommunication", "Reponse sent to client #%d\n", pid);
        
        free(request.payload);
        free(responsePayload);

        if(request.requestType == C_EXIT_BAR){
            logInfo(stdout, "clientCommunication", "Client #%d exited bar\n", pid);
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
        logError(stderr, "communicationProcess", "Error while parsing arguments");
        exit(EXIT_FAILURE);
    }
    logInfo(stdout, "communicationProcess", "Parsed args for communication process pid \"%d\"\n", pidClient);

    listeningSocket = createTCPSocket(localListeningPort);
    if(listeningSocket == -1){
        logError(stderr, "communicationProcess", "Error while creating TCP socket");
        close(listeningSocket);
        exit(EXIT_FAILURE);
    }
    logInfo(stdout, "communicationProcess", "Created TCP Socket - process pid \"%d\"\n", pidClient);

    statusCode = listen(listeningSocket, MAX_REQUESTS);
    if(statusCode == -1){
        logError(stderr, "communicationProcess", "Error trying to listen for messages");
        close(listeningSocket);
        exit(EXIT_FAILURE);
    }
    logInfo(stdout, "communicationProcess", "Listening for client requests - process pid \"%d\"\n", pidClient);

    while(1){
        lgAddress = sizeof(struct sockaddr_in);
        serviceSocket = accept(listeningSocket, (struct sockaddr*)&clientAddress, &lgAddress);
        if(serviceSocket == -1){
            logError(stderr, "communicationProcess", "Error while accepting incoming connection from: \"%s\"", clientAddress.sin_addr.s_addr);
            exit(EXIT_FAILURE);
        }
        if((fork()) == 0){
            close(listeningSocket);
            statusCode = clientCommunication(serviceSocket);
            if(statusCode == -1){
                logError(stderr, "communicationProcess", "Something went wrong with clientCommunication");
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
    int shmid, statusCode, i;

    shmid = retrieveTapSHM(SHM_KEY, N_TAPS);
    if(shmid == -1){
        logError(stderr, "controlProcess", "Error retrieving SHM");
        exit(EXIT_FAILURE);
    }
    logInfo(stdout, "controlProcess", "Retrieved Tap SHM");

    taps = attachTapSHM(shmid);
    if(taps == NULL){
        logError(stderr, "controlProcess", "Unable to attach to SHM");
        exit(EXIT_FAILURE);
    }
    logInfo(stdout, "controlProcess", "Attached Tap SHM");
    
    statusCode = openTapSemaphore(semaphore, N_TAPS, SEM_KEY);
    if(statusCode == -1){
        logError(stderr, "controlProcess", "Error opening semaphore");
        exit(EXIT_FAILURE);
    }
    logInfo(stdout, "controlProcess", "Opened Tap semaphore");

    logInfo(stdout, "controlProcess", "Keg's are being now monitored");
    while(statusCode == 0){
        for(i = 0; i < N_TAPS; i++){
            statusCode = checkKeg(semaphore[i], &taps[i], i);
            if(statusCode == -1){
                logError(stderr, "controlProcess", "error checking keg %d", i);
            }
        }
        sleep(2);
    }
    logInfo(stdout, "controlProcess", "Keg's are no longer being monitored");
    
    if(detachTapSHM(taps) == -1){
        logError(stderr, "controlProcess", "Error detaching from tap");
        exit(EXIT_FAILURE);
    }

    if(closeTapSemaphore(semaphore, N_TAPS) == -1){
        logError(stderr, "controlProcess", "Error closing semaphores");
        exit(EXIT_FAILURE);
    }


    exit(EXIT_SUCCESS);
}

void mainProcess(){
    tap_t* taps;
    sem_t* semaphore[N_TAPS];
    int shmid, statusCode; 
    char buffer[BUFFER];
    char* beerName;
    char* end;
    char* p;
    long reqType, chosenBeer, chosenSize;
    int i;

    // int sock;
    // char* response;

    // SHM w semaphore 
    shmid = retrieveTapSHM(SHM_KEY, N_TAPS);
    if(shmid == -1){
        logError(stderr, "mainProcess", "Error retrieving SHM");
        exit(EXIT_FAILURE);
    }
    logInfo(stdout, "mainProcess", "Retrieve tap SHM");

    taps = attachTapSHM(shmid);
    if(taps == NULL){
        logError(stderr, "mainProcess", "Unable to attach to SHM");
        exit(EXIT_FAILURE);
    }
    logInfo(stdout, "mainProcess", "Attach tap SHM");
    
    statusCode = openTapSemaphore(semaphore, N_TAPS, SEM_KEY);
    if(statusCode == -1){
        logError(stderr, "mainProcess", "Error opening semaphore");
        exit(EXIT_FAILURE);
    }
    logInfo(stdout, "mainProcess", "Opened sem for tap");

// 
    // sock = createUDPSocket(0);
    // if(sock == -1){
    //     logError(stderr, "controlProcess", "Unable to create UDP socket");
    //     exit(EXIT_FAILURE);
    // }

    // statusCode = exchangeUDPSocket(sock, "localhost", 7777, 50003, "bonjour from C", &response, BUFFER);
    // if(statusCode == -1){
    //     logError(stderr, "controlProcess", "Unable to send message via UDP socket");
    //     exit(EXIT_FAILURE);
    // }

    // logInfo(stdout, "controlProcess", "Got from server \"%s\"", response);
// 

    while(statusCode >= 0){
        if(receivePipe(PIPE_CLIENT_MAIN, buffer, BUFFER) == -1){
            logError(stderr, "mainProcess", "Error receiving from %s", PIPE_CLIENT_MAIN);
            exit(EXIT_FAILURE);
        }

        reqType = strtol(buffer, &end, 10);
        if(end == buffer || errno == ERANGE){
            logError(stderr, "mainProcess", "Error converting requestType %s", buffer);
            exit(EXIT_FAILURE);
        }
        
        switch(reqType){
            case C_AVAILABLE_BEER:
                strcpy(buffer, "");
                for(i = 0; i < N_TAPS; i++){
                    beerName = getBeerName(semaphore[i], &taps[i]);
                    if(beerName == NULL){
                        logError(stderr, "mainProcess", "Unable to get beer name for #%d", i);
                        exit(EXIT_FAILURE);
                    }

                    strcat(buffer, beerName);
                    free(beerName);
                    if(i+1 < N_TAPS){
                        strcat(buffer, ",");
                    }
                }
                break;
            case C_ORDER_BEER:
                p = end;
                chosenBeer = strtol(p, &end, 10);
                if(end == p || *end != ','){
                    logError(stderr, "mainProcess", "Unable to convert chosen beer");
                    exit(EXIT_FAILURE);
                }

                p = end + 1;
                chosenSize = strtol(p, &end, 10);
                if(end == p || *end != '\0'){
                    logError(stderr, "mainProcess", "Unable to convert chosen size");
                    exit(EXIT_FAILURE);
                }
                
                strcpy(buffer, "");
                if(chosenBeer < 1 || chosenBeer > N_TAPS){
                    strcat(buffer, "Beer number not recognised");
                    break;
                } else if(!(chosenSize == 1 || chosenSize == 2)){
                    strcat(buffer, "Beer size not recognised");
                    break;
                }

                if(serveBeer(semaphore[chosenBeer-1], &taps[chosenBeer-1], (chosenSize == 1) ? PINT_QTY : HALF_PINT_QTY) == -1){
                    logError(stderr, "mainProcess", "Unable to serve given beer");
                    exit(EXIT_FAILURE);
                }

                strcat(buffer, "Beer served!");
                break;
            default:
                logError(stderr, "mainProcess", "Request not recognised #d", reqType);
                exit(EXIT_FAILURE);
        }

        if(sendPipe(PIPE_MAIN_CLIENT, buffer, sizeof(char)*(strlen(buffer) + 1)) == -1){
            logError(stderr, "mainProcess", "Error sending from %s", PIPE_MAIN_CLIENT);
            statusCode = -1;
            exit(EXIT_FAILURE);
        }

    }

    if(detachTapSHM(taps) == -1){
        logError(stderr, "mainProcess", "Error detaching tap");
        exit(EXIT_FAILURE);
    }

    if(closeTapSemaphore(semaphore, N_TAPS) == -1){
        logError(stderr, "mainProcess", "Error closing semaphore");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}

int main(int argc, char** argv){
    pid_t pidProcesses[NUM_PROC];
    int currentPidIndex;
    
    if(createPipe(PIPE_MAIN_CLIENT) == -1){
        logError(stderr, "main", "Unable to create pipe named %s", PIPE_MAIN_CLIENT);
        exit(EXIT_FAILURE);
    }

    if(createPipe(PIPE_CLIENT_MAIN) == -1){
        logError(stderr, "main", "Unable to create pipe named %s", PIPE_CLIENT_MAIN);
        exit(EXIT_FAILURE);
    }
    
    // Main
    pidProcesses[0] = launchNewProcess("Main", &mainProcess);
    if(pidProcesses[0] == -1){
        logError(stderr, "main", "Error launching main process");
        exit(EXIT_FAILURE);
    }

    // Communication
    pidProcesses[0] = launchNewProcess("Communication", &communicationProcess, argc, argv);
    if(pidProcesses[0] == -1){
        logError(stderr, "main", "Error launching communication process");
        exit(EXIT_FAILURE);
    }

    // Controle
    pidProcesses[2] = launchNewProcess("Control", &controlProcess);
    if(pidProcesses[2] == -1){
        logError(stderr, "main", "Error launching control process");
        exit(EXIT_FAILURE);
    }


    sleep(2);
    currentPidIndex = 0;
    while(1){
        logInfo(stdout, "main", "Continuing with pid %d", pidProcesses[currentPidIndex]);
        kill(pidProcesses[currentPidIndex], SIGCONT);

        sleep(QUANTUM);

        logInfo(stdout, "main", "Stopping pid %d", pidProcesses[currentPidIndex]);
        kill(pidProcesses[currentPidIndex], SIGSTOP);

        if(checkProcessStatus(pidProcesses, NUM_PROC) == -1){
            logError(stderr, "main", "Checking the health of processes faile");
            terminateAll(pidProcesses, NUM_PROC);
            break;
        } else{
            currentPidIndex = getNextProcessIndex(currentPidIndex, NUM_PROC);
        }
    }

    terminateAll(pidProcesses, NUM_PROC);

    return EXIT_SUCCESS;
}