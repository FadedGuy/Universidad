#ifndef PROCESS
#define PROCESS

/**
 * Checks the status of all processes, if any are not Ok all processes are terminated
 * @param pids Array containing pids to check
 * @param nPids Size of the array
 * @return 0 on success of all processes, -1 for errors
*/
int checkProcessStatus(const pid_t pids[], const int nPids);

/**
 * Terminates all processes in the array
 * @param pids Array of pid to terminate
 * @param nPids Size of array
*/
void terminateAll(const pid_t pids[], const int nPids);

/**
 * Loops through all the processes and returns the next one
 * @param currentPidIndex Current pid
 * @param nPids Number of pids to loop through
*/
int getNextProcessIndex(const int currentPidIndex, const int nPids);

/**
 * Launches func as a new process, the function must use exit as a return
 * @param funcName Function name to identify
 * @param func Pointer to a function 
 * @param ... Arguments for the function, if any
 * @return Process pid on sucess, -1 for errors
*/
pid_t launchNewProcess(const char* funcName, void (*func)(), ...);

#endif