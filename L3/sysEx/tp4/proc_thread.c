#include <sys/wait.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/shm.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>    

#define N_PHIL 5

typedef struct {
    sem_t *arg0;
    int arg1;
    int arg2;
    int arg3;
} ThreadArgs;

union semun {
    int val;
    struct semi_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
};

// P(S)
void custom_wait(int semid, int sem_num) {
    struct sembuf buf;

    buf.sem_op = -1;
    buf.sem_flg = 0;
    buf.sem_num=sem_num;
    semop(semid, &buf, 1);
    
}

// V(S)
void custom_post(int semid, int sem_num){
    struct sembuf buf;

    buf.sem_op =1;
    buf.sem_flg =0;
    buf.sem_num=sem_num;
    semop(semid, &buf, 1);

}

void philosopher(int id, int semid, int *baguette) {
    int left = id;
    int right = (id + 1) % N_PHIL;

    while(1) {
        printf("Philosophe %d reflechit..\n", id);
        usleep(rand()%500000);
        custom_wait(semid, left);
        custom_wait(semid, right);

        printf("Philosophe %d mange.. \n", id);
        usleep(rand()%500000);

        custom_post(semid, right);
        custom_post(semid, left);
    }
}


int main() {
    int i;
    int semid;
    sem_t baguettes[N_PHIL];
    pthread_t philo[N_PHIL];

    srand(time(NULL));

    semid = semget(IPC_PRIVATE, N_PHIL, IPC_CREAT | 0666);
    for(i = 0; i < N_PHIL; i++) {
        semctl(semid, i, SETVAL, 1);
    }

    for(i = 0; i < N_PHIL; i++) {
        ThreadArgs* args = malloc(sizeof(ThreadArgs));
        args->arg0 = baguettes;
        args->arg1 = i;
        args->arg2 = N_PHIL;
        args->arg3 = 0;
        pthread_create(&philo[i], NULL, philosopher, args);
    }

    for(i = 0; i < N_PHIL; i++) {
        pthread_join(philo[i], NULL);
    }

    semctl(semid, 0, IPC_RMID, 0);
    return 0;
}