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

void sort_process_sjf(struct Process *proc, int n){
    int i, j;
    struct Process temp;
    for(i = 0; i < n; i++){
        for(j = i+1; j < n; j++){
            // Sort by arrival
            if(proc[i].arrival_time > proc[j].arrival_time) {
                temp = proc[i]; 
                proc[i] = proc[j];
                proc[j] = temp;
            }
            // Sort by burst_time, can add prio also
            else if(proc[i].arrival_time == proc[j].arrival_time && proc[i].burst_time > proc[j].burst_time){
                temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
}

void sort_process_prio(struct Process *proc, int n){
    int i, j;
    struct Process temp;
    for(i = 0; i < n; i++){
        for(j = i+1; j < n; j++){
            // Sort by priority
            if(proc[i].priority < proc[j].priority) {
                temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
}


void print_process(struct Process *proc){
    printf("ID: %d\tArrival: %d\tBurst: %d\tPriority: %s\n", proc->id, proc->arrival_time, proc->burst_time, str_priority[proc->priority]);
}
