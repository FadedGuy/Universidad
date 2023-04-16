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
    int status, i;
    float missingQuantity;


    sleep(1);
    if(( status = shmget(SHM_KEY, sizeof(tap_t)*N_TAPS, 0))==-1) {
        printf("shm2.shmget: %s\n", strerror(errno));
        exit(1);
    }
    printf("status = %d\n", status);
    if(( taps =(tap_t*) shmat(status, NULL, 0)) == (tap_t*)-1){
        printf("shm2.shmat: %s\n", strerror(errno));
        exit(1);
    }
    
    for(i = 0; i < N_TAPS; i++){
        if((semaphore[i] = sem_open(SEM_KEY, O_CREAT, 0666, 1)) == SEM_FAILED){
            printf("sem_open: %s\n", strerror(errno));
            exit(1);
        }
    }

    sem_wait(semaphore[0]);
    printf("Before: taps = %p, *taps = %d %f \n", (void*)taps, taps[0].type, taps[0].quantity);
    missingQuantity = taps[0].quantity;
    sem_post(semaphore[0]);
    sleep(2);

    while(missingQuantity > 0){
        printf("Sleeping for 2 seconds\n");
        sleep(2);
   
        sem_wait(semaphore[0]);
        printf("Serving: taps = %p, *taps = %d %f \n", (void*)taps, taps[0].type, taps[0].quantity);
        taps[0].quantity -= 0.5;
        missingQuantity = taps[0].quantity;
        sem_post(semaphore[0]);

        sleep(0.5);
    }

    if(shmdt(taps) == -1) {
        printf("shm2.shmdt: %s\n", strerror(errno));
        exit(1);
    }
    if(shmctl(status, IPC_RMID, NULL) == -1) {
        printf("shm2.shmctl: %s\n", strerror(errno));
        exit(1);
    }

    for(i = 0; i < 2; i++){
        if(sem_close(semaphore[i]) == -1){
            printf("sem_close: %s\n", strerror(errno));
            exit(1);
        }
    }

    return EXIT_SUCCESS;
}