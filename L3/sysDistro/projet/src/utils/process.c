#include <errno.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

#include "logger.h"
#include "process.h"

int checkProcessStatus(const pid_t pids[], const int nPids){
    pid_t terminated;
    int i, status;

    terminated = waitpid(-1, &status, WNOHANG);
    for(i = 0; i < nPids; i++){
        if(terminated == pids[i]){
            if(WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE){
                logErrorWithArgs("Process #%d with pid %d has failed", i, pids[i]);
                terminateAll(pids, nPids);
                return -1;
            }
        } else if(terminated == -1){
            logError("Error waiting for processes");
            return -1;
        }
    }

    return 0;
}

void terminateAll(const pid_t pids[], const int nPids){
    int i;

    for(i = 0; i < nPids; i++){
        if(kill(pids[i], SIGTERM) == -1){
            if(errno != ESRCH){
                logErrorWithArgs("Error sending signal to process #%d with pid %d: %s", i, pids[i], strerror(errno));
            }
        }
    }
}

int getNextProcessIndex(const int currentPidIndex, const int nPids){
    return (currentPidIndex + 1 < nPids) ? currentPidIndex+1 : 0;
}

pid_t launchNewProcess(const char* funcName, void (*func)(), ...){
    pid_t pid;
    va_list args;

    pid = fork();
    if(pid == -1){
        logErrorWithArgs("Unable to start process named \"%s\"", funcName);
        return -1;
    } else if(pid == 0){
        logInfoWithArgs("Initializing process named \"%s\"\n", funcName);
        va_start(args, func);
        func(args);
        va_end(args);
        logInfo("Process initialized");        
    }

    return pid;
}
