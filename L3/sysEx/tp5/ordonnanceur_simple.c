#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

#define N_PROCESSES 5

char str_priority[5][10] = {"Lowest", "Low", "Default", "High", "Highest"};
enum Priority{
    LOWEST = 0,
    LOW,
    DEFAULT,
    HIGH,
    HIGHEST
};

struct Process{
    int id;
    int execTime;
    enum Priority priority;
};

int main(){
    int i;
    struct Process proc[N_PROCESSES];

    srand(time(NULL));

    for(i = 0; i < N_PROCESSES; i++){
        proc[i].id = i;
        proc[i].execTime = (rand()%5)+1;
        proc[i].priority = rand()%4;
    }

    for(i = 0; i < N_PROCESSES; i++){
        printf("ID: %d\tTime:%d\tPriority: %s\n", proc[i].id, proc[i].execTime, str_priority[proc[i].priority]);
    }


    return 0;
}