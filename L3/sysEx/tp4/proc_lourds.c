#include <sys/wait.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/shm.h>
#include <time.h>
#include <unistd.h>

#define N_PHIL 5

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

void philosopher(int id, int semid) {
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
    int baguettes;

    srand(time(NULL));

    semid = semget(IPC_PRIVATE, N_PHIL, IPC_CREAT | 0666);
    printf("%d\n\n",semid);
    for(i = 0; i < N_PHIL; i++) {
        semctl(semid, i, SETVAL, 1);
    }

    // for(i = 0; i < N_PHIL; i++) {
    //     if(fork()==0) {
    //         philosopher(i, semid);
    //         exit(0);
    //     }
    // }

    // for(i = 0; i < N_PHIL; i++) {
    //     wait(NULL);
    // }

    semctl(semid, 0, IPC_RMID, 0);
    return 0;
}