#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>

#include "calculs.h"
#include "fonction.h"

#define TAILLEBUF 50


void traiter_communication(int socket){
    struct request req;
    int nb_octets, size;
    printf(".. client connecte\n");
    while(1){
        nb_octets = read(socket, (struct request*)&req, sizeof(struct request));
        if(nb_octets <= 0){
            perror("error receiving data1\n");
            break;
        }

        if(req.type == FACTORIEL){
            int nb;
            long res;
            nb_octets = read(socket, &nb, sizeof(int));
            if(nb_octets <= 0){
                perror("error receiving data2\n");
                break;
            }

            res = factoriel(nb);

            if(write(socket, (char*)&res, sizeof(long)) <= 0){
                perror("error receiving data3\n");
                break;                
            }
        }
        if(req.type == PUISSANCE){
            int x, puis;
            int res;
            int var[2];

            nb_octets = read(socket, &var, req.size_request);
            if(nb_octets <= 0){
                perror("error receiving data2\n");
                break;
            }            
            res = puissance(var[0], var[1]);

            if(write(socket, (char*)&res, sizeof(int)) <= 0){
                perror("error receiving data3\n");
                break;                
            }
        }
        if(req.type == STATS){
            int size;
            int arr[6];
            struct res_analyse_donnees res;
            
            nb_octets = read(socket, &arr, req.size_request);
            if(nb_octets <= 0){
                perror("error receiving data2\n");
                break;
            }

            analyser_donnees(arr+1, arr[0], &res);

            if(write(socket, (char*)&res, sizeof(struct res_analyse_donnees)) <= 0){
                perror("error receiving data3\n");
                break;                
            }
        }
    }

    printf(".. client deconnecte\n");
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

    // Multiconnexion
    while(1){
        lg_addr = sizeof(struct sockaddr_in);
        socket_service = accept(socket_ecoute, (struct sockaddr*)&addr_client, &lg_addr);
        if(socket_service == -1){
            perror("Listening error");
            exit(1);
        }
        if(fork() == 0){
            close(socket_ecoute);
            traiter_communication(socket_service);
            exit(0);
        }

        close(socket_service);
    }
    
    close(socket_ecoute);

    return 0;
}