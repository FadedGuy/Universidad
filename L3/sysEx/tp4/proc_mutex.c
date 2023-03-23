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
pthread_mutex_t mutex[N_PHIL];

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

void *philosopher(void *args) {
    ThreadArgs arguments = *((ThreadArgs*)args); 
    int left = arguments.id % N_PHIL;
    int id = left;
    int right = (left + 1) % N_PHIL;
    int semid = arguments.semid;

    while(1) {
        printf("Philosophe %d reflechit..\n", id+1);
        sleep(1);
        usleep(rand()%500000);
        pthread_mutex_lock(&mutex[left]);
        printf("Philosophe %d prend la baguette gauche %d\n", id+1, left);
        pthread_mutex_lock(&mutex[right]);
        printf("Philosophe %d prend la baguette droite  %d\n", id+1, right);
        sleep(1);
        printf("Philosophe %d mange.. \n", id+1);
        sleep(1);
        usleep(rand()%500000);
        pthread_mutex_unlock(&mutex[left]);
        printf("Philosophe %d pose la baguette gauche %d\n", id+1, left);
        pthread_mutex_unlock(&mutex[right]);
        printf("Philosophe %d pose la baguette droite  %d\n", id+1, right);
        sleep(1);
    }
    
}


int main() {
    int i;
    int semid;
    pthread_t philo[N_PHIL];
    ThreadArgs* args = (ThreadArgs*)malloc(sizeof(ThreadArgs)*N_PHIL);

    srand(time(NULL));

    semid = semget(IPC_PRIVATE, N_PHIL, IPC_CREAT | 0666);

    for(i = 0; i < N_PHIL; i++){
        pthread_mutex_init(&mutex[i], NULL);
        semctl(semid, i, SETVAL, 1);
        args[i].id = i;
        args[i].semid = semid;
    }    

    for(i = 0; i < N_PHIL; i++) {
        pthread_create(&philo[i], NULL, philosopher, &args[i]);
    }

    for(i = 0; i < N_PHIL; i++) {
        pthread_join(philo[i], NULL);
    }

    for(i = 0; i < N_PHIL; i++){
        pthread_mutex_destroy(&mutex[i]);
    }

    semctl(semid, 0, IPC_RMID, 0);
    return 0;
}