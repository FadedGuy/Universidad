#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0
typedef int BOOL;

typedef struct s_message
{
    int id;
    char* msg;
    BOOL vide;
    int destinataire;
    BOOL transmis;
    BOOL recu;  
}*message;

message creer();
message editer(message, char*);
message envoyer(message, int);
message accuserReception(message);

int identifiant(message);
char* contenu(message);
int destinataire(message);

BOOL estVide(message);
BOOL estTransmis(message);
BOOL estRecu(message);
