#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "process.h"

#define N_PROCESSES 5

int main(){
    int n, i, j;
    float avg_wait_time = 0, avg_turn_time = 0;
    struct Process proc[N_PROCESSES];

    srand(time(NULL));
    for(int i = 0; i < N_PROCESSES; i++){
        random_initialize_process(proc + i);
        proc[i].id = i;
    }
    sort_process_sjf(proc, N_PROCESSES);

    // Abstract stats
    int completion_time[N_PROCESSES], waiting_time[N_PROCESSES], turnaround_time[N_PROCESSES];
    completion_time[0] = proc[0].burst_time;
    turnaround_time[0] = completion_time[0] - proc[0].arrival_time;
    waiting_time[0] = turnaround_time[0] - proc[0].burst_time;
    avg_wait_time += waiting_time[0];
    avg_turn_time += turnaround_time[0];
    for(i = 1; i < N_PROCESSES; i++) {
        completion_time[i] = completion_time[i-1] + proc[i].burst_time;
        turnaround_time[i] = completion_time[i] - proc[i].arrival_time;
        waiting_time[i] = turnaround_time[i] - proc[i].burst_time;
        avg_wait_time += waiting_time[i];
        avg_turn_time += turnaround_time[i];
    }
    avg_wait_time /= N_PROCESSES;
    avg_turn_time /= N_PROCESSES;

    printf("Avg Wait: %f\tAvg Turn: %f\n", avg_wait_time, avg_turn_time);
    for(int i = 0; i < N_PROCESSES; i++){
        print_process(proc + i);
    }
    for(int i = 0; i < N_PROCESSES; i++){
        printf("%d %d %d\n", completion_time[i], waiting_time[i], turnaround_time[i]);
    }

    return 0;    
}