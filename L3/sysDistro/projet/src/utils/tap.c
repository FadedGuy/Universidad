#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <semaphore.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "logger.h"
#include "tap.h"

static char* beer_type_string[] = {
    "Paix Dieu",
    "Kwak",
};

int createTapSHM(int key, int nTaps){
    int shmid;

    shmid = shmget(key, nTaps*sizeof(tap_t), IPC_CREAT|IPC_EXCL|0666);
    if(shmid == -1){
        if(errno == EEXIST){
            shmid = retrieveTapSHM(key, nTaps);
            removeTapSHM(shmid);
            logError(stderr, "createTapSHM", "Removed shm because it existed, creating a new one");
            return createTapSHM(key, nTaps);
        } else{
            logError(stderr, "createTapSHM", "Error while creating SHM with key \"%d\": %s", key, strerror(errno));
            return -1;
        }
    }
    return shmid;
}

int retrieveTapSHM(int key, int nTaps){
    int id;

    id = shmget(key, nTaps*sizeof(tap_t), 0);
    if(id == -1){
        logError(stderr, "retrieveTapSHM", "Error while retrieving SHM with key \"%d\": %s", key, strerror(errno));
        return -1;
    }

    return id;
}

tap_t* attachTapSHM(const int shmid){
    tap_t* value;

    value = shmat(shmid, NULL, 0);
    if(value == (tap_t*) -1){
        logError(stderr, "attachTapSHM", "Unable to attach to SHM with id: \"%d\". Code: %s", shmid, strerror(errno));
        return NULL;
    }

    return value;
}

int detachTapSHM(tap_t* taps){
    if(shmdt(taps) == -1){
        logError(stderr, "detachTapSHM", "Error detaching from SHM: %s", strerror(errno));
        return -1;
    }

    return 0;
}

int removeTapSHM(const int shmid){
    if(shmctl(shmid, IPC_RMID, NULL) == -1){
        logError(stderr, "removeTapSHM", "Unable to remove SHM: %s", strerror(errno));
        return -1;
    }

    return 0;
}

int openTapSemaphore(sem_t* semaphore[], const int semSize, const char* key){
    int i;

    for(i = 0; i < semSize; i++){
        semaphore[i] = sem_open(key, O_CREAT, 0666, 1);
        if(semaphore[i] == SEM_FAILED){
            logError(stderr, "openTapSemaphore", "Error opening semaphore \"%s\" in index \"%d\"", key, i);
            return -1;
        }
    }

    return 0;
}

int closeTapSemaphore(sem_t* semaphore[], const int semSize){
    int i;

    for(i = 0; i < semSize; i++){
        if(sem_close(semaphore[i]) == -1){
            logError(stderr, "closeTapSemaphore", "Error closing semaphore index \"%d\": %s", i, strerror(errno));
            return -1;
        }
    }
    
    return 0;
}

int initializeTap(sem_t* sem, tap_t* tap, beer_type_t type){
    if(sem_wait(sem) == -1){
        logError(stderr, "initializeTap", "Error waiting for semaphore access");
        return -1;
    }

    if(strlen(beer_type_string[type-1]) >= MAX_LENGTH_NAME){
        logError(stderr, "initializeTap", "Unable to assign tap name size %d because max size is %d", strlen(beer_type_string[type-1]), MAX_LENGTH_NAME);
        return -1;
    }
    strcpy(tap->name, beer_type_string[type-1]);
    tap->type = type;
    tap->quantity = KEG_CAPACITY;
    tap->capacity = KEG_CAPACITY;

    if(sem_post(sem) == -1){
        logError(stderr, "initializeTap", "Error releasing semaphore");
        return -1;
    }

    return 0;
}

int serveBeer(sem_t* sem, tap_t* tap, const float qty){
    float remaining = 0;
    int sleepTime = 0;

    if(sem_wait(sem) == -1){
        logError(stderr, "serveBeer", "Error waiting for semaphore access");
        return -1;
    }

    logInfo(stdout, "serveBeer", "Preparing to serve beer...");
    if(tap->quantity - qty < 0){
        logError(stderr, "serveBeer", "Not enough beer left");
        return -1;
    }

    tap->quantity -= qty;
    remaining = tap->quantity;
    
    if(qty == PINT_QTY){
        sleepTime = SERVE_PINT_TIME;
    }
    else if(qty == HALF_PINT_QTY){
        sleepTime = SERVE_HALF_PINT_TIME;
    }

    sleep(sleepTime);
    logInfo(stdout, "serveBeer", "Served \"%f\". Remaining in %d type keg: \"%f\"\n", qty, tap->type, remaining);

    if(sem_post(sem) == -1){
        logError(stderr, "serveBeer", "Error releasing semaphore");
        return -1;
    }

    return remaining;
}

int getQuantity(sem_t* sem, tap_t* tap){
    float remaining = 0;

    if(sem_wait(sem) == -1){
        logError(stderr, "getQuantity", "Error waiting for semaphore access");
        return -1;
    }

    remaining = tap->quantity;

    if(sem_post(sem) == -1){
        logError(stderr, "getQuantity", "Error releasing semaphore");
        return -1;
    }

    return remaining;
}

int checkKeg(sem_t* sem, tap_t* tap, int id){
    float missing;
    int sock, statusCode;

    
    missing = getQuantity(sem, tap);
    if(missing == -1){
        logError(stderr, "checkKeg", "Error retrieving keg levels for tap %d", id);
        return -1;
    } else if(missing == 0){
        printf("Controle -> WE NEED MORE BEEEEEEEEEEEEEEEEEEEEEEEER on tap %d\n", id);
        // Here goes controle -> commande
        printf("Controle -> Ordering more beer\n");
        sem_wait(sem);
        tap->quantity = tap->capacity;
        //init test with java
        // sock = createUDPSocket(0);
        // if(sock == -1){
        //     logError(stderr, "controlProcess", "Unable to create UDP socket");
        //     exit(EXIT_FAILURE);
        // }

        // statusCode = exchangeUDPSocket(sock, "localhost", 7777, "bonjour from C", &response, BUFFER);
        // if(statusCode == -1){
        //     logError(stderr, "controlProcess", "Unable to send message via UDP socket");
        //     exit(EXIT_FAILURE);
        // }
        // logInfo(stdout, "controlProcess", "Got from server \"%s\"", response);
        //fin test with java
        printf("Controle -> Beer has been refilled on tap %d %f\n", id, tap->capacity);
        sem_post(sem);
    }

    return 0;
}

int initSHM(const int key, const int nTaps, tap_t** taps){
    int id;

    id = createTapSHM(key, nTaps);
    if(id == -1){
        logError(stderr, "initSHM", "Error creating SHM");
        return -1;
    }

    
    *taps = attachTapSHM(id);
    if(*taps == NULL){
        logError(stderr, "initSHM", "Unable to attach to SHM");
        return -1;
    }

    return id;
}

char* getBeerName(sem_t* sem, tap_t* tap){
    char* name = malloc(sizeof(char)*MAX_LENGTH_NAME);
    if(name == NULL){
        logError(stderr, "getBeerName", "Unable to allocate memory for name");
        return NULL;
    }

    if(sem_wait(sem) == -1){
        logError(stderr, "getBeerName", "Error waiting for semaphore access");
        return NULL;
    }

    strcpy(name, tap->name);

    if(sem_post(sem) == -1){
        logError(stderr, "getBeerName", "Error releasing semaphore");
        return NULL;
    }

    return name;
}