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
    // id server
    struct hostent *serveur_host;
    // ip socket server
    static struct sockaddr_in addr_serveur;
    // size socket ip
    socklen_t lg;
    // local socket descriptor
    int sock;
    // str to send
    char *msg = "bonjour";
    // buffer response
    char buffer[TAILLEBUF];
    // str response
    char *reponse;
    // nb bytes read or sent
    int nb_octets;

    // Parse from command line parameters
    if(argc != 3){
        perror("Incorrect usage. Use: ./client nom_serveur port_serveur");
        exit(1);
    }
    char* nom_serveur = argv[1];
    char* end;
    long port_serveur = strtol(argv[2], &end, 10);
    if(argv[2] == end  || errno == ERANGE){
        perror("Unable to parse port");
        exit(1);
    }

    sock = creerSocketUDP(0);
    if(sock == -1){
        perror("Unable to create socket");
        exit(1);
    }

    // get server id
    serveur_host = gethostbyname(nom_serveur);
    if(serveur_host == NULL){
        perror("Error retrieving server ip");
        exit(1);
    }

    // create socket ip destination
    bzero(&addr_serveur, sizeof(struct sockaddr_in));
    addr_serveur.sin_family = AF_INET;
    addr_serveur.sin_port = htons(port_serveur);
    memcpy(&addr_serveur.sin_addr.s_addr, serveur_host->h_addr, serveur_host->h_length);

    // Send message to server
    lg = sizeof(struct sockaddr_in);
    nb_octets = sendto(sock, msg, strlen(msg)+1, 0, (struct sockaddr*)&addr_serveur, lg);
    if(nb_octets == -1){
        perror("Error sending message");
        exit(1);
    }
    printf("Paquet sent, nb_octets=%d\n", nb_octets);
    
    // Wait for server response
    nb_octets = recvfrom(sock, buffer, TAILLEBUF, 0, (struct sockaddr*)&addr_serveur, &lg);
    if(nb_octets == -1){
        perror("Server response error");
        exit(1);
    }
    reponse = (char*)malloc(nb_octets*sizeof(char));
    memcpy(reponse, buffer, nb_octets);
    printf("Response from server: %s\n", reponse);

    // Close socket
    close(sock);

    return 0;
}
