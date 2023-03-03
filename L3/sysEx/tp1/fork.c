#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    int n_fils;
    pid_t fils_pid;
    
    scanf("%d", &n_fils);
    for(int i = 1; i <= n_fils; i++){
        fils_pid = fork();
        switch(fils_pid){
            case -1:
                // Error fork
                fprintf(stderr, "Fork failure\n");
                perror("fork");
                exit(-1);
            case 0:
                // fil code
                printf("%d: fils et fils_pid=%d\n", getpid(), fils_pid);
                break;
            default:
                // pere code
                printf("%d : pere, creation de fils reussie, fils_pid = %d\n", getpid(), fils_pid);
                break;
        }
    }

    return 0;
}