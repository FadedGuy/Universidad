#ifndef PROCESS
#define PROCESS

enum Priority{
    LOWEST = 0,
    LOW,
    DEFAULT,
    HIGH,
    HIGHEST
};

struct Process{
    int id;
    int arrival_time;
    int burst_time;
    enum Priority priority;
};

void random_initialize_process(struct Process *proc);
void print_process(struct Process *proc);

#endif