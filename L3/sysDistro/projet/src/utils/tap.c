#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/shm.h>

#include <semaphore.h>
#include <fcntl.h>

#include "logger.h"
#include "tap.h"
#include "util.h"

#define BUFFER 50

struct tap_t{
    BeerType type;
    char        name[MAX_LENGTH_NAME];
    float       quantity;
    float       capacity;
};

// Initial beer kegs
static char* beer_name_string[MAX_LENGTH_NAME] = {
    "Paix Dieu",
    "Kwak",
};

static char* beer_type_string[] = {
    "AMBER",
    "LAGER"
};

int createTapSHM(int key, int nTaps){
    int shmid;

    shmid = shmget(key, nTaps*sizeof(Tap), IPC_CREAT|IPC_EXCL|0666);
    if(shmid == -1){
        if(errno == EEXIST){
            shmid = retrieveTapSHM(key, nTaps);
            removeTapSHM(shmid);
            logError("Removed shm because it existed, creating a new one");
            return createTapSHM(key, nTaps);
        } else{
            logErrorWithArgs("Error while creating SHM with key \"%d\": %s", key, strerror(errno));
            return -1;
        }
    }
    return shmid;
}

int retrieveTapSHM(int key, int nTaps){
    int id;

    id = shmget(key, nTaps*sizeof(Tap), 0);
    if(id == -1){
        logErrorWithArgs("Error while retrieving SHM with key \"%d\": %s", key, strerror(errno));
        return -1;
    }

    return id;
}

Tap* attachTapSHM(const int shmid){
    Tap* value;

    value = shmat(shmid, NULL, 0);
    if(value == (Tap*) -1){
        logErrorWithArgs("Unable to attach to SHM with id: \"%d\". Code: %s", shmid, strerror(errno));
        return NULL;
    }

    return value;
}

int detachTapSHM(Tap* taps){
    if(shmdt(taps) == -1){
        logErrorWithArgs("Error detaching from SHM: %s", strerror(errno));
        return -1;
    }

    return 0;
}

int removeTapSHM(const int shmid){
    if(shmctl(shmid, IPC_RMID, NULL) == -1){
        logErrorWithArgs("Unable to remove SHM: %s", strerror(errno));
        return -1;
    }

    return 0;
}

int openTapSemaphore(sem_t* semaphore[], const int semSize, const char* key){
    int i;

    for(i = 0; i < semSize; i++){
        semaphore[i] = sem_open(key, O_CREAT, 0666, 1);
        if(semaphore[i] == SEM_FAILED){
            logErrorWithArgs("Error opening semaphore \"%s\" in index \"%d\"", key, i);
            return -1;
        }
    }

    return 0;
}

int closeTapSemaphore(sem_t* semaphore[], const int semSize){
    int i;

    for(i = 0; i < semSize; i++){
        if(sem_close(semaphore[i]) == -1){
            logErrorWithArgs("Error closing semaphore index \"%d\": %s", i, strerror(errno));
            return -1;
        }
    }
    
    return 0;
}

int initializeTap(sem_t* sem, Tap* tap, BeerType type){
    if(sem_wait(sem) == -1){
        logError("Error waiting for semaphore access");
        return -1;
    }

    if(strlen(beer_name_string[type-1]) >= MAX_LENGTH_NAME){
        logErrorWithArgs("Unable to assign tap name size %d because max size is %d", strlen(beer_name_string[type-1]), MAX_LENGTH_NAME);
        return -1;
    }
    strcpy(tap->name, beer_name_string[type-1]);
    tap->type = type;
    tap->quantity = KEG_CAPACITY;
    // Change to this if testing control
    // tap->quantity = 1.0;
    tap->capacity = KEG_CAPACITY;

    if(sem_post(sem) == -1){
        logError("Error releasing semaphore");
        return -1;
    }

    return 0;
}

int serveBeer(sem_t* sem, Tap* tap, const float qty){
    float remaining = 0;
    int sleepTime = 0;

    if(sem_wait(sem) == -1){
        logError("Error waiting for semaphore access");
        return -1;
    }

    logInfo("Preparing to serve beer...");
    if(tap->quantity - qty < 0){
        logError("Not enough beer left");
        if(sem_post(sem) == -1){
            logError("Error releasing semaphore");
            return -1;
        }
        return -2;
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
    logInfoWithArgs("Served \"%f\". Remaining in %d type keg: \"%f\"\n", qty, tap->type, remaining);

    if(sem_post(sem) == -1){
        logError("Error releasing semaphore");
        return -1;
    }

    return remaining;
}

float getQuantity(sem_t* sem, Tap* tap){
    float remaining;

    if(sem_wait(sem) == -1){
        logError("Error waiting for semaphore access");
        return -1;
    }

    remaining = tap->quantity;

    if(sem_post(sem) == -1){
        logError("Error releasing semaphore");
        return -1;
    }

    return remaining;
}

int checkKeg(sem_t* sem, Tap* tap, int id){
    float missing;
    int sock, statusCode;
    int i;
    char* response;
    char* message; 
    char* resName;

    missing = getQuantity(sem, tap);
    if(missing == -1){
        logErrorWithArgs("Error retrieving keg levels for tap %d", id);
        return -1;
    } else if(missing == 0){
        logInfoWithArgs("More beer is needed for tap with id %d", id);

        response = malloc(sizeof(char) * BUFFER); 
        resName = malloc(sizeof(char) * MAX_LENGTH_NAME);
        message = malloc(sizeof(char) * BUFFER);
        if(response == NULL || resName == NULL || message == NULL){
            logError("Unable to allocate memory");
            return -1;
        }

        sock = createUDPSocket(0);
        if(sock == -1){
            logError("Unable to create UDP socket");
            free(response);
            free(resName);
            return -1;
        }

        strcpy(message, getBeerName(sem, tap));
        strcat(message, " ");
        strcat(message, beer_type_string[getBeerType(sem, tap)-1]);

        statusCode = exchangeUDPSocket(sock, "localhost", PROVIDER_SEND_PORT, PROVIDER_RECEIVE_PORT, message, response);
        if(statusCode == -1){
            logError("Unable to send message via UDP socket");
            free(response);
            free(resName);
            free(message);
            logInfo("Trying request again in 2 seconds");
            sleep(2);
            return checkKeg(sem, tap, id);
        }else if(response == NULL){
            logError("Response from the server was empty");
            free(response);
            free(resName);
            free(message);
            logInfo("Trying request again in 2 seconds");
            sleep(2);
            return checkKeg(sem, tap, id);
        } else if(response[0] == '1'){
            logError("Request to the server was not sucessful");
            free(response);
            free(resName);
            free(message);
            logInfo("Trying request again in 2 seconds");
            sleep(2);
            return checkKeg(sem, tap, id);
        }

        for(i = strlen(response)-1; i >= 0; i--){
            if(response[i] == ' '){
                strncpy(resName, response+2, i-1);
                break;
            }
        }
        resName[i-2] = '\0'; 

        if(i == -1){
            logError("Response from server is not recognized");
            free(response);
            free(resName);
            free(message);
            return -1;
        }  

        if(setTapName(sem, tap, resName) == -1){
            logError("Unable to update tap name");
            free(response);
            free(resName);
            free(message);
            return -1;
        }

        if(setTapTypeFromString(sem, tap, response+i) == -1){
            logError("Unable to update tap type");
            free(response);
            free(resName);
            free(message);
            return -1;
        }

        if(refillTap(sem, tap) == -1){
            logError("Unable to refill tap");
            free(response);
            free(resName);
            free(message);
            return -1;
        }

        logInfoWithArgs("New keg of beer has been set on tap %d with name %s", id, resName);
        free(response);
        free(resName);
        free(message);

    }

    return 0;
}

int initSHM(const int key, const int nTaps, Tap** taps){
    int id;

    id = createTapSHM(key, nTaps);
    if(id == -1){
        logError("Error creating SHM");
        return -1;
    }
    
    *taps = attachTapSHM(id);
    if(*taps == NULL){
        logError("Unable to attach to SHM");
        return -1;
    }

    return id;
}

char* getBeerName(sem_t* sem, Tap* tap){
    char* name = malloc(sizeof(char)*MAX_LENGTH_NAME);
    if(name == NULL){
        logError("Unable to allocate memory for name");
        return NULL;
    }

    if(sem_wait(sem) == -1){
        logError("Error waiting for semaphore access");
        return NULL;
    }

    strcpy(name, tap->name);

    if(sem_post(sem) == -1){
        logError("Error releasing semaphore");
        return NULL;
    }

    return name;
}

int getBeerType(sem_t* sem, Tap* tap){
    BeerType type;
    if(sem_wait(sem) == -1){
        logError("Error waiting for semaphore access");
        return -1;
    }

    type = tap->type;

    if(sem_post(sem) == -1){
        logError("Error releasing semaphore");
        return -1;
    }
    
    return type;
}

int refillTap(sem_t* sem, Tap* tap){
    int refilledQty;

    if(sem_wait(sem) == -1){
        logError("Error waiting for semaphore access");
        return -1;
    }

    tap->quantity = tap->capacity;
    refilledQty = tap->quantity;

    if(sem_post(sem) == -1){
        logError("Error releasing semaphore");
        return -1;
    }

    return refilledQty;
}

int setTapName(sem_t* sem, Tap* tap, const char* name){
    if(sem_wait(sem) == -1){
        logError("Error waiting for semaphore access");
        return -1;
    }

    if(strlen(name) > MAX_LENGTH_NAME){
        logErrorWithArgs("New name %s is size %d and the max size allowed is %s", name, strlen(name), MAX_LENGTH_NAME);
        return -1;
    }

    strcpy(tap->name, name);

    if(sem_post(sem) == -1){
        logError("Error releasing semaphore");
        return -1;
    }

    return 0;
}

int setTapType(sem_t* sem, Tap* tap, const BeerType type){
    if(sem_wait(sem) == -1){
        logError("Error waiting for semaphore access");
        return -1;
    }

    tap->type = type;

    if(sem_post(sem) == -1){
        logError("Error releasing semaphore");
        return -1;
    }

    return 0;
}

int setTapTypeFromString(sem_t* sem, Tap* tap, const char* type){
    int i;
    char* typeStrUpper = malloc(sizeof(char) * strlen(type));
    if(typeStrUpper == NULL){
        logError("Unable to allocate memory");
        return -1;
    }

    for(i = 0; i < strlen(type); i++){
        typeStrUpper[i] = toupper(type[i]);
    }

    if(sem_wait(sem) == -1){
        logError("Error waiting for semaphore access");
        return -1;
    }

    for(i = 0; i < N_TAPS; i++){
        if(strcmp(typeStrUpper, beer_type_string[i]) == 0){
            tap->type = i;
        }
    }
    
    if(sem_post(sem) == -1){
        logError("Error releasing semaphore");
        return -1;
    }

    free(typeStrUpper);

    return 0;
}

Tap* getTapFromIndex(Tap* taps, const int index){
    if(index >= 0 && index < N_TAPS){
        return &taps[index];
    }

    return NULL;
}