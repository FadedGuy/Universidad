#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#include "pipe.h"
#include "util.h"

int createPipe(const char* name){
    if(access(name, F_OK) != -1){
        if(unlink(name) == -1){
            printError("Unable to delete existent pipe with same name %s", name);
            return -1;
        }
    }

    if(mkfifo(name, 0666) == -1){
        printError("Error creating FIFO named %s", name);
        return -1;
    }

    return 0;
}

int sendPipe(const char* name, const char* message, const int messageSize){
    int pipe, nbBytes;

    pipe = open(name, O_WRONLY);
    if(pipe == -1){
        printError("Unable to open pipe named \"%s\" to send a message", name);
        return -1;
    }

    nbBytes = write(pipe, message, messageSize);
    if (nbBytes == -1) {
        printError("Unable to write message to pipe \"%s\"", name);
        close(pipe);
        return -1;
    } else if (nbBytes < messageSize) {
        printError("Partial write to pipe \"%s\"", name);
        close(pipe);
        return -1;
    }

    close(pipe);
    return 0;
}

int receivePipe(const char* name, char* buffer, int bufferSize) {
    int pipe, nbBytes;

    pipe = open(name, O_RDONLY);
    if (pipe == -1) {
        printError("Unable to open pipe named \"%s\" to receive a message", name);
        return -1;
    }

    nbBytes = read(pipe, buffer, bufferSize);
    if (nbBytes == -1) {
        printError("Unable to read message from pipe \"%s\"", name);
        close(pipe);
        return -1;
    }

    close(pipe);
    return nbBytes;
}
