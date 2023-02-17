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

#define TAILLEBUF 20

void write_file(int sock){
    int n;
    FILE *file = fopen("file_received.txt", "w");
    char buffer[TAILLEBUF];

    while(1){
        n = recv(sock, buffer, TAILLEBUF, 0);
        if(n <= 0){
            break;
            return;
        }
        
        fprintf(file, "%s", buffer);
        bzero(buffer, TAILLEBUF);
    }
    return;
}

int main(int argc, char** argv){
    // IP socket client side
    static struct sockaddr_in addr_client;
    // IP local socket
    static struct sockaddr_in addr_server;
    // length ip
    int lg_addr;
    // listening and service socket
    int socket_ecoute, socket_service;
    // buffer message received
    char message[TAILLEBUF];
    // str received client
    char *chaine_recue;
    // str sent client
    char* reponse = "bien recu";
    // nb bytes received, sent
    char nb_octets;

    // Parse from command line parameters
    if(argc != 2){
        perror("Incorrect usage. Use: ./serveur port_local_ecoute");
        exit(1);
    }
    char* end;
    long port_local_ecoute = strtol(argv[1], &end, 10);
    if(argv[1] == end || errno == ERANGE){
        perror("Unable to parse port");
        exit(1);
    }

    socket_ecoute = creerSocketTCP(port_local_ecoute);
    if(socket_ecoute == -1){
        perror("Error creating socket");
        exit(1);
    }

    // Send message
    if(listen(socket_ecoute, 5) == -1){
        perror("Error listening for messages");
        exit(1);
    }

    // Wait client connection
    lg_addr = sizeof(struct sockaddr_in);
    socket_service = accept(socket_ecoute, (struct sockaddr*)&addr_client, &lg_addr);
    if(socket_service == -1){
        perror("Listening error");
        exit(1);
    }

    // Wait for client message
    // nb_octets = read(socket_service, message, TAILLEBUF);
    write_file(socket_service);

    // Show message
    // chaine_recue = (char*) malloc(nb_octets*sizeof(char));
    // memcpy(chaine_recue, message, nb_octets);
    // printf("Message received: %s", chaine_recue);

    // Send response
    write(socket_service, reponse, strlen(reponse)+1);

    // close sockets
    close(socket_service);
    close(socket_ecoute);

    return 0;
}