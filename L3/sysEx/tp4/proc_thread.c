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
    int semid;
    int id;
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

void *philosopher(void *args) {
    ThreadArgs arguments = *((ThreadArgs*)args); 
    int left = arguments.id % N_PHIL;
    int id = left;
    int right = (left + 1) % N_PHIL;
    int semid = arguments.semid;


    while(1) {
        printf("Philosophe %d reflechit..\n", id+1);
        usleep(rand()%500000);
        custom_wait(semid, left);
        custom_wait(semid, right);

        printf("Philosophe %d mange.. \n", id+1);
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
    ThreadArgs* args = (ThreadArgs*)malloc(sizeof(ThreadArgs)*N_PHIL);

    srand(time(NULL));

    semid = semget(IPC_PRIVATE, N_PHIL, IPC_CREAT | 0666);
    printf("%d\n\n", semid);
    for(i = 0; i < N_PHIL; i++) {
        semctl(semid, i, SETVAL, 1);
        args[i].id = i;
        args[i].semid = semid;
        pthread_create(&philo[i], NULL, philosopher, &args[i]);
    }

    for(i = 0; i < N_PHIL; i++) {
        pthread_join(philo[i], NULL);
    }

    semctl(semid, 0, IPC_RMID, 0);
    return 0;
}