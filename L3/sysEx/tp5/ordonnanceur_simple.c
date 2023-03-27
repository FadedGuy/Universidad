#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include "process.h"

#define N_PROCESSES 5

int main(){
    int i;
    struct Process proc[N_PROCESSES];

    srand(time(NULL));

    for(i = 0; i < N_PROCESSES; i++){
        random_initialize_process(proc + i);
        proc[i].id = i;
    }

    sort_process_prio(proc, N_PROCESSES);

    for(i = 0; i < N_PROCESSES; i++){
        print_process(proc + i);
    }


    return 0;
}