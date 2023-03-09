#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

typedef struct {
    sem_t *arg0;
    int arg1;
    int arg2;
    int arg3;
} ThreadArgs;

void *miam(void *arg) {
    int* valueg = malloc(sizeof(int));
    int* valued = malloc(sizeof(int));
    ThreadArgs* args = (ThreadArgs*) arg;
    int i = args->arg1;
    int miam = args->arg3;
    sem_init(&args->arg0[i],0,1);
    sleep(2);
   while(miam < 4){
    
        
        //printf("La valeur du semaphore est : %d\n", value);

       //printf("%d : mmmmmmmmmmmmmmmmmmm\n", i); //le philosophe pense
        
        sem_getvalue(&args->arg0[i], valued);
        sem_getvalue(&args->arg0[(i+(args->arg2-1))%(args->arg2)], valueg);

        //printf("%d avant miam : fougauche (%d) = %d fourdroite (%d) = %d\n",i+1, (i+(args->arg2-1))%(args->arg2),*valueg, i, *valued);
        //printf("%d : JAI FAIM !!!!! HAAAAAA\n", i); //le philosophe prend les fourchettes
        if(i == 0){
            sem_wait(&args->arg0[i]);
            sem_wait(&args->arg0[(i+(args->arg2-1))%(args->arg2)]);
        }
        else{
            
            sem_wait(&args->arg0[(i+(args->arg2-1))%(args->arg2)]);
            sem_wait(&args->arg0[i]);
        }
        
        

        
        //printf("La valeur du semaphore est : %d\n", value);
//
        ////printf("%d : AAHAMMIAMIMAIMIAMIAMMMSLRRRRRMMMMMMMM\n", i); //le philosophe mange
        //
        printf("philosophe n°%d : (%d)\n", i+1, miam); //le philosophe a fini, il repose les fourchettes*
        miam++;
        sem_post(&args->arg0[i]);
        sem_post(&args->arg0[(i+(args->arg2-1))%(args->arg2)]);
        sleep(rand() % 4);
       //
//
        //
//
//
    }
    printf("%d : repus\n", i+1);
}

int main(){
    int nb_philo;
  
    printf("combien de philosophes ? ");
    scanf("%d",&nb_philo);

    pthread_t philo[nb_philo];
    sem_t fourchette[nb_philo];

    

    for (int i = 0; i < nb_philo; i++){
        
        ThreadArgs* args = malloc(sizeof(ThreadArgs));
        args->arg0 = fourchette;
        args->arg1 = i;
        args->arg2 = nb_philo;
        args->arg3 = 0;
        pthread_create(&philo[i], NULL, miam, args);
    }
    
    for (int i = 0; i< nb_philo; i++){
        pthread_join(philo[i], NULL);
    }
    
    return 0;
}