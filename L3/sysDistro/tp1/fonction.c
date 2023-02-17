#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>

#include "fonction.h"

int creerSocketUDP(int port){
    // ip local socket
    static struct sockaddr_in addr_local;
    // descriptor local socket
    int sock;

    // create socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock == -1){
        return -1;
    }

    // Let system decide on port 
    if(port == 0){
        return sock;
    }

    bzero(&addr_local, sizeof(struct sockaddr_in));
    addr_local.sin_family = AF_INET;
    addr_local.sin_port = htons(port);
    addr_local.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(sock, (struct sockaddr*)&addr_local, sizeof(addr_local)) == -1){
        return -1;
    }

    return sock;
}