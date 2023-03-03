#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int traiter(char* prog, char** args){
    pid_t fils_pid;
    fils_pid = fork();
    if(fils_pid != 0){
        return fils_pid;
    }
    else{
        execvp(prog, args);
        perror("Error in execvp\n");
        return -1;
    }
}

int main(int argc, char** argv){
    int ret;

    ret = traiter(argv[1], argv+1);
    printf("Processus principal %d termine avec ret=%d\n", getpid(), ret);
    return 0;
}