#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <string.h>

#include "util.h"
#include "process.h"

int checkProcessStatus(const pid_t pids[], const int nPids){
    pid_t terminated;
    int i, status;

    terminated = waitpid(-1, &status, WNOHANG);
    for(i = 0; i < nPids; i++){
        if(terminated == pids[i]){
            if(WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE){
                printError("Process #%d with pid %d has failed", i, pids[i]);
                terminateAll(pids, nPids);
                return -1;
            }
        } else if(terminated == -1){
            printError("Error waiting for processes");
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
                printError("Error sending signal to process #%d with pid %d: %s", i, pids[i], strerror(errno));
            }
        }
    }
}

int getNextProcessIndex(const int currentPidIndex, const int nPids){
    return (currentPidIndex + 1 < nPids) ? currentPidIndex+1 : 0;
}