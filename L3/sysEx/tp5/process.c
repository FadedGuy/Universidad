#include "process.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

const char str_priority[5][10] = {"Lowest", "Low", "Default", "High", "Highest"};

void random_initialize_process(struct Process *proc){
    proc->arrival_time = rand()%10 + 1;
    proc->burst_time = rand()%10 + 1;
    proc->priority = rand()%4;
}

void print_process(struct Process *proc){
    printf("ID: %d\tArrival: %d\tBurst: %d\tPriority: %s\n", proc->id, proc->arrival_time, proc->burst_time, str_priority[proc->priority]);
}
