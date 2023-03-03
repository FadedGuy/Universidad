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

#define TAILLEBUF 50
#define N 500

void send_file(FILE *fp, int sock){
    int n;
    char data[TAILLEBUF];

    while(fgets(data, TAILLEBUF, fp) != NULL){
        if(send(sock, data, sizeof(data), 0) == -1){
            perror("Error sending file");
            exit(1);
        }
        bzero(data, TAILLEBUF);
    }
    printf("File sent\n");
}

int main(int argc, char** argv){
    // Id listening socket server
    static struct sockaddr_in addr_serveur;
    // id server machine
    struct hostent* serveur_host;
    // local client socket
    int sock;
    // str to send
    char message[TAILLEBUF];
    // FILE *file = fopen("file.txt", "r");
    // str to receive
    char reponse[TAILLEBUF];
    // nb bytes received/send
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

    // create TCP socket
    sock = creerSocketTCP(0);

    // Get id server machine
    serveur_host = gethostbyname(nom_serveur);
    if(serveur_host == NULL){
        perror("Error retrieving server IP");
        exit(1);
    }

    // create socket id for listening socket
    bzero((char*)&addr_serveur, sizeof(addr_serveur));
    addr_serveur.sin_family = AF_INET;
    addr_serveur.sin_port = htons(port_serveur);
    memcpy(&addr_serveur.sin_addr.s_addr, serveur_host->h_addr, serveur_host->h_length);

    // connect local client socket to server socket
    if(connect(sock, (struct sockaddr*)&addr_serveur, sizeof(struct sockaddr_in)) == -1){
        perror("Error connecting to server");
        exit(1);
    }

    // Envoyer message personnalise
    // function_number params
    // factoriel = 0, nb
    // analyse_donnees = 1, donnees, taille(?)
    // puissance = 2, nb, puiss
    int opc, nb, puiss, taille;
    int donnees[N];
    do{
        printf("Message to send: ");
        scanf("%d", &opc);
    }while(opc < 0 && opc > 3);
    
    sprintf(message, "%d", opc);
    printf("%s\n", message);

    switch (opc)
    {
        case 0:
            scanf("%d", &nb);
            break;
        case 1:
            
            break;
        case 2:
            
            break;
    }

    // Send message
    nb_octets = write(sock, message, strlen(message)+1);
    // send_file(file, sock);
    
    // Wait response
    nb_octets = read(sock, reponse, TAILLEBUF);
    printf("Reponse: %s\n", reponse);

    // Close socket
    close(sock);

    return 0;
}