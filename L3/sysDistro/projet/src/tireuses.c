#include <errno.h>
#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>


#include "utils/tap.h"
#include "utils/logger.h"

int main(){
    tap_t* taps;
    sem_t* semaphore[N_TAPS];
    int shmid, statusCode, i;

    shmid = initSHM(SHM_KEY, N_TAPS, &taps);
    if(shmid == -1){
        logError(stderr, "main", "Error initializing SHM");
        exit(EXIT_FAILURE);
    }
    logInfo(stdout, "main", "Created sem");

    statusCode = openTapSemaphore(semaphore, N_TAPS, SEM_KEY);
    if(statusCode == -1){
        logError(stderr, "main", "Error opening semaphore");
        exit(EXIT_FAILURE);
    }
    logInfo(stdout, "main", "Opened sem");

    for(i = 0; i < N_TAPS; i++){
        statusCode = initializeTap(semaphore[i], &taps[i], i+1);
        if(statusCode == -1){
            logError(stderr, "main", "Error initializing tap \"%d\" with type \"%d\"", 0, i+1);
            exit(EXIT_FAILURE);
        }
        logInfo(stdout, "main", "Tap %d initialized", i);
    }
    logInfo(stdout, "main", "Taps initialized");

    sleep(200);
        
    if(detachTapSHM(taps) == -1){
        logError(stderr, "main", "Error detaching from tap");
        exit(EXIT_FAILURE);
    }

    if(closeTapSemaphore(semaphore, N_TAPS) == -1){
        logError(stderr, "main", "Error closing semaphores");
        exit(EXIT_FAILURE);
    }

    removeTapSHM(shmid);

    return EXIT_SUCCESS;
}