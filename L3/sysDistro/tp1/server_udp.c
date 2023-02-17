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

int main(int argc, char** argv){
    // ip local socket
    static struct sockaddr_in addr_local;
    // ip socket of server
    static struct sockaddr_in addr_serveur;
    static struct sockaddr_in addr_client;
    // id client
    struct hostent *host_client;
    // size ip socket
    socklen_t lg;
    // descriptor local socket
    int sock;
    // str to send
    char *reponse = "bien recu";
    // reception buffer
    char buffer[TAILLEBUF];
    // received str
    char *chaine;
    // nb bytes sent or received
    int nb_octets;

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

    sock = creerSocketUDP(port_local_ecoute);
    if(sock == -1){
        perror("Error creating socket");
        exit(1);
    }

    // Wait for client data
    lg = sizeof(struct sockaddr_in);
    nb_octets = recvfrom(sock, buffer, TAILLEBUF, 0, (struct sockaddr*)&addr_client, &lg);
    if(nb_octets == -1){
        perror("Error receiving package");
        exit(1);
    }

    // Retrieve pc name that send data
    host_client = gethostbyaddr(&(addr_client.sin_addr), sizeof(long), AF_INET);
    if(host_client == NULL){
        perror("Error gethostbyaddr");
        exit(1);
    }

    // Show message received and sender data
    chaine = (char*) malloc(nb_octets*sizeof(char));
    memcpy(chaine, buffer, nb_octets);
    printf("Received message: %s from %s on port %d\n", chaine, host_client->h_name, ntohs(addr_client.sin_port));

    // Send response to sender
    nb_octets = sendto(sock, reponse, strlen(reponse)+1, 0, (struct sockaddr*)&addr_client, lg);
    if(nb_octets == -1){
        perror("Error sending response");
        exit(1);
    }

    // Close socket
    close(sock);

    return 0;
}