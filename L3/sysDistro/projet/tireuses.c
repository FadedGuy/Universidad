#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <semaphore.h>
#include <fcntl.h>

#include "tap.h"
#include "util.h"

int main(){
    tap_t* taps;
    sem_t* semaphore[N_TAPS];
    int shmid, statusCode;
    float missingQuantity;

    shmid = retrieveTapSHM(SHM_KEY, N_TAPS);
    if(shmid == -1){
        printError("Error retrieving SHM");
        exit(EXIT_FAILURE);
    }

    taps = attachTapSHM(shmid);
    if(taps == NULL){
        printError("Unable to attach to SHM");
        exit(EXIT_FAILURE);
    }
    
    statusCode = openTapSemaphore(semaphore, N_TAPS, SEM_KEY);
    if(statusCode == -1){
        printError("Error opening semaphore");
        exit(EXIT_FAILURE);
    }

    while(missingQuantity >= 0){
        printf("Sleeping for 2 seconds\n");
        sleep(2);
   
        missingQuantity = serveBeer(semaphore[1], &taps[1], PINT_QTY);
        if(missingQuantity == -1){
            printError("Unable to serve more beer\n");
        }

        printf("\n");
        sleep(0.5);
    }

    
    if(detachTapSHM(taps) == -1){
        printError("Error detaching from tap");
        exit(EXIT_FAILURE);
    }

    if(closeTapSemaphore(semaphore, N_TAPS) == -1){
        printError("Error closing semaphores");
        exit(EXIT_FAILURE);
    }


    return EXIT_SUCCESS;
}