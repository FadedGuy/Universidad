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
#include "calculs.h"

#define TAILLEBUF 50
#define N 500

long factoriel_client(int num, int sock){
    struct request req;
    char* message;
    int size;
    long res;

    req.type = FACTORIEL;
    req.size_request = sizeof(int);

    size = sizeof(struct request) + req.size_request;
    message = (char*)malloc(size);
    memcpy(message, &req, sizeof(struct request));
    memcpy(message+sizeof(struct request), &num, sizeof(int));

    if(write(sock, message, size) <= 0){
        free(message);
        return -1;
    }
    if(read(sock, (long*)&res, sizeof(long)) <= 0){
        free(message);
        return -1;
    }

    free(message);
    return res;
} 

long puissance_client(int x, int puis, int sock){
    struct request req;
    char* message;
    int size;
    long res;

    req.type = PUISSANCE;
    req.size_request = sizeof(int)*2;

    size = sizeof(struct request) + req.size_request;
    message = (char*)malloc(size);
    memcpy(message, &req, sizeof(struct request));
    memcpy(message+sizeof(struct request), &x, sizeof(int));
    memcpy(message+sizeof(struct request)+sizeof(int), &puis, sizeof(int));

    if(write(sock, message, size) <= 0){
        free(message);
        return -1;
    }
    if(read(sock, (long*)&res, sizeof(long)) <= 0){
        free(message);
        return -1;
    }

    free(message);
    return res;

}

struct res_analyse_donnees donnees_client(int donnees[], int size_donnees, int sock){
    struct request req;
    char* message;
    int size;
    struct res_analyse_donnees res;

    req.type = STATS;
    req.size_request = sizeof(int)*(size_donnees+1);

    size = sizeof(struct request) + req.size_request;
    message = (char*)malloc(size);
    memcpy(message, &req, sizeof(struct request));
    memcpy(message+sizeof(struct request), &size_donnees, sizeof(int));
    memcpy(message+sizeof(struct request)+sizeof(int), &donnees, sizeof(int)*size_donnees);

    if(write(sock, message, size) <= 0){
        free(message);
        return res;
    }
    if(read(sock, (struct res_analyse_donnees*)&res, sizeof(struct res_analyse_donnees)) <= 0){
        free(message);
        return res;
    }

    free(message);
    return res;    
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

    // long nb = 5;
    // long res = factoriel_client(nb, sock);
    // if(res == -1){
    //     perror("Error factoriel");
    //     exit(1);
    // }
    // printf("Le factoriel de %ld est: %ld\n", nb, res);

    // long x = 5, puis = 5;
    // long res = puissance_client(x, puis, sock);
    // if(res == -1){
    //     perror("Error puissance");
    //     exit(1);
    // }
    // printf("La puissance de %ld^%ld est: %ld\n", x, puis, res);

    int taille = 5;
    int arr[] = {4,5,7,1,5};
    struct res_analyse_donnees res = donnees_client(arr, taille, sock);
    printf("Les donnees sont: %f, %d, %d\n", res.moy, res.max, res.min);

    return 0;
}