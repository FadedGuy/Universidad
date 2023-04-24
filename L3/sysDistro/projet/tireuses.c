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
    int shmid, statusCode, i;

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

    sleep(15);
        
    if(detachTapSHM(taps) == -1){
        printError("Error detaching from tap");
        exit(EXIT_FAILURE);
    }

    if(closeTapSemaphore(semaphore, N_TAPS) == -1){
        printError("Error closing semaphores");
        exit(EXIT_FAILURE);
    }

    removeTapSHM(shmid);

    return EXIT_SUCCESS;
}