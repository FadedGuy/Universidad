#include <stdlib.h>
#include <unistd.h>

#include <semaphore.h>

#include "utils/logger.h"
#include "utils/tap.h"

int main(){
    Tap* taps;
    sem_t* semaphore[N_TAPS];
    int shmid, statusCode, i;

    shmid = initSHM(SHM_KEY, N_TAPS, &taps);
    if(shmid == -1){
        logError("Error initializing SHM");
        exit(EXIT_FAILURE);
    }
    logInfo("Created sem");

    statusCode = openTapSemaphore(semaphore, N_TAPS, SEM_KEY);
    if(statusCode == -1){
        logError("Error opening semaphore");
        exit(EXIT_FAILURE);
    }
    logInfo("Opened sem");

    for(i = 0; i < N_TAPS; i++){
        statusCode = initializeTap(semaphore[i], getTapFromIndex(taps, i), i+1);
        if(statusCode == -1){
            logErrorWithArgs("Error initializing tap \"%d\" with type \"%d\"", 0, i+1);
            exit(EXIT_FAILURE);
        }
        logInfoWithArgs("Tap %d initialized", i);
    }
    logInfo("Taps initialized");

    sleep(200);
        
    if(detachTapSHM(taps) == -1){
        logError("Error detaching from tap");
        exit(EXIT_FAILURE);
    }

    if(closeTapSemaphore(semaphore, N_TAPS) == -1){
        logError("Error closing semaphores");
        exit(EXIT_FAILURE);
    }

    removeTapSHM(shmid);

    return EXIT_SUCCESS;
}