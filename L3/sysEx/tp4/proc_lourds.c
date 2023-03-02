#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/shm.h>
#include <time.h>
#include <unistd.h>

#define KEYPHIL 99
#define N_PHIL 5
#define DROITE(i) (i+1)%5
#define GAUCHE(i) (i-1)%5

union semun {
    int val;
    struct semi_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
};

sem_t baguette[N_PHIL];

// P(S)
// void custom_wait(int semid) {
//     struct sembuf *buf;
    
//     // Traitement baguette avec semid
//     buf->sem_num = 0;
//     buf->sem_flg = 0;
//     buf->sem_op = -1;
    
//     semop(semid, &buf, 1);
// }

// // V(S)
// void custom_post(int semid){
//     // struct sembuf *buf;

//     // // Traitement baguette avec semid
//     // buf->sem_op = 1;
    
//     // semop(semid, &buf, 1);
// }


int main() {
    int semid;
    int count;  
    struct sembuf buf;

    semid = semget(KEYPHIL, N_PHIL, IPC_CREAT);
    sem_init(semid, 0, 0);
    pid_t fils_pid;
    srand(time(NULL));
    // creating fils_pid
    for(int i = 0; i < N_PHIL; i++){
        switch (fils_pid=fork()) {
            case -1: /* échec du fork */
                fprintf(stderr, "échec du fork \n");
                perror("fork");
                exit(-1);
            case 0: /* code du fils */
                count = (rand() % 3) + 1;

                while(count){
                    sem_wait(&baguette[GAUCHE((int)fils_pid)]);
                    sem_wait(&baguette[DROITE((int)fils_pid)]);
                    printf("Philosopher %d mange\n", (int)fils_pid);
                    sem_post(&baguette[GAUCHE((int)fils_pid)]);
                    sem_post(&baguette[DROITE((int)fils_pid)]); 

                    count--;
                }
                exit(0);

            default: /* code du père */
                break;
        }
    }

    semctl(semid, 0, IPC_RMID, baguette);

    return 0;
}