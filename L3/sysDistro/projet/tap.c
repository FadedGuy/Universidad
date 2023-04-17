#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <semaphore.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "util.h"
#include "tap.h"

/* 
    Auto sem_wait-sem_post with function as param
*/

static const char* beer_type_string[] = {
    "Amber",
    "Lager",
};

int createTapSHM(int key, int nTaps){
    int shmid;

    shmid = shmget(key, nTaps*sizeof(tap_t), IPC_CREAT|IPC_EXCL|0666);
    if(shmid == -1){
        if(errno == EEXIST){
            shmid = retrieveTapSHM(key, nTaps);
            removeTapSHM(shmid);
            printError("Removed shm because it existed, creating a new one");
            return createTapSHM(key, nTaps);
        } else{
            printError("Error while creating SHM with key \"%d\": %s", key, strerror(errno));
            return -1;
        }
    }
    return shmid;
}

int retrieveTapSHM(int key, int nTaps){
    int id;

    id = shmget(key, nTaps*sizeof(tap_t), 0);
    if(id == -1){
        printError("Error while retrieving SHM with key \"%d\": %s", key, strerror(errno));
        return -1;
    }

    return id;
}

tap_t* attachTapSHM(const int shmid){
    tap_t* value;

    value = shmat(shmid, NULL, 0);
    if(value == (tap_t*) -1){
        printError("Unable to attach to SHM with id: \"%d\". Code: %s", shmid, strerror(errno));
        return NULL;
    }

    return value;
}

int detachTapSHM(tap_t* taps){
    if(shmdt(taps) == -1){
        printError("Error detaching from SHM: %s", strerror(errno));
        return -1;
    }

    return 0;
}

int removeTapSHM(const int shmid){
    if(shmctl(shmid, IPC_RMID, NULL) == -1){
        printError("Unable to remove SHM: %s", strerror(errno));
        return -1;
    }

    return 0;
}

int openTapSemaphore(sem_t* semaphore[], const int semSize, const char* key){
    int i;

    for(i = 0; i < semSize; i++){
        semaphore[i] = sem_open(key, O_CREAT, 0666, 1);
        if(semaphore[i] == SEM_FAILED){
            printError("Error opening semaphore \"%s\" in index \"%d\"", key, i); 
            return -1;
        }
    }

    return 0;
}

int closeTapSemaphore(sem_t* semaphore[], const int semSize){
    int i;

    for(i = 0; i < semSize; i++){
        if(sem_close(semaphore[i]) == -1){
            printError("Error closing semaphore index \"%d\": %s", i, strerror(errno));
            return -1;
        }
    }
    
    return 0;
}

int initializeTap(sem_t* sem, tap_t* tap, beer_type_t type){
    if(sem_wait(sem) == -1){
        printError("Error waiting for semaphore access");
        return -1;
    }

    if(strlen(beer_type_string[type-1]) >= MAX_LENGTH_NAME){
        printError("Unable to assign tap name size %d because max size is %d", strlen(beer_type_string[type-1]), MAX_LENGTH_NAME);
        return -1;
    }
    strcpy(tap->name, beer_type_string[type-1]);
    tap->type = type;
    tap->quantity = KEG_CAPACITY;
    tap->capacity = KEG_CAPACITY;

    if(sem_post(sem) == -1){
        printError("Error releasing semaphore");
        return -1;
    }

    return 0;
}

int serveBeer(sem_t* sem, tap_t* tap, const float qty){
    float remaining = 0;

    if(sem_wait(sem) == -1){
        printError("Error waiting for semaphore access");
        return -1;
    }

    printf("Preparing to serve beer...\n");
    if(tap->quantity - qty < 0){
        printError("Unable to serve beer");
        return -1;
    }

    tap->quantity -= qty;
    remaining = tap->quantity;
    printf("Served \"%f\". Remaining in %d type keg: \"%f\"\n", qty, tap->type, remaining);

    if(sem_post(sem) == -1){
        printError("Error releasing semaphore");
        return -1;
    }

    return remaining;
}