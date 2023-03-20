#include <sys/types.h> // pour pid_t
#include <unistd.h> // pour fork()
#include <stdio.h> // pour printf
#include <stdlib.h>
#include <sys/wait.h>
#include "semaphore.h"

void miam(sem_t *f, int id, int nb_fils){
    
    int* valueg = malloc(sizeof(int));
    int* valued = malloc(sizeof(int));

   
  

    sem_getvalue(&f[id], valued);
    sem_getvalue(&f[(id+(nb_fils-1))%(nb_fils)], valueg);
    //printf("%d avant miam : fougauche (%d) = %d fourdroite (%d) = %d\n",id+1, (id+(nb_fils-1))%(nb_fils),*valueg, id, *valued);
    int miam = 0;
    while(miam < 4){
        sem_getvalue(&f[id], valued);
        sem_getvalue(&f[(id+(nb_fils-1))%(nb_fils)], valueg);

        if(id == 1){
            sem_wait(&f[id]);
            sem_wait(&f[(id+(nb_fils-1))%(nb_fils)]);
        }
        else{
            
            sem_wait(&f[(id+(nb_fils-1))%(nb_fils)]);
            sem_wait(&f[id]);
        }

        printf("philosophe n°%d : (%d)\n", id+1, miam); //le philosophe a fini, il repose les fourchettes*
        miam++;
        
        
        sem_post(&f[id]);
        sem_post(&f[(id+(nb_fils-1))%(nb_fils)]);
        sleep(rand() % 4);
    }
    
    printf("%d : repus\n", id+1);


    
    
}


int main(){
    int papa = getpid();
    int nb_fils;
    

    printf("choisir un nb de philosophe : \n");
    scanf("%d",&nb_fils);
    sem_t* fourchette = malloc(nb_fils * sizeof(sem_t));
    for (int i =0 ; i < nb_fils ; i++){
       sem_init(&fourchette[i],0,1);
       
    }

    for (int i = 0; i<nb_fils-1; i++){
        
        
        
        fork();
      
        if(getpid() != papa){
                
            miam(fourchette,i, nb_fils);
            i = nb_fils;
            
        }
        else{
            if(i == nb_fils-2){
               
                miam(fourchette,i+1, nb_fils);
            }
        }
        
    }

    //printf("je suis %d\n",getpid());
}