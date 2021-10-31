#include "message.h"

message creer()
{
    message newMsg;
    newMsg = malloc(sizeof(message));
    if(newMsg == NULL)
    {
        fprintf(stderr, "Allocation impossible\n");
        exit(EXIT_FAILURE); 
    }
    srand(time(NULL));
    newMsg->id = rand();
    strcpy(newMsg->msg, "");

    newMsg->vide = TRUE;
    newMsg->transmis = FALSE;
    newMsg->recu = FALSE;
    return newMsg;
}

message editer(message msg, char* txt)
{
    msg->vide = FALSE;
    strcpy(msg->msg, txt);
    return msg;
}

message envoyer(message msg, int destinataire)
{
    msg->destinataire = destinataire;
    msg->transmis = TRUE;
    return msg;
}

message accuserReception(message msg)
{
    if(!estTransmis(msg) && estRecu(msg))
    {
        fprintf(stderr, "Erreur dans l'accuse de recepcion");
    }
    return msg;
}

int identifiant(message msg)
{
    return msg->id;
}

char* contenu(message msg)
{
    return msg->msg;
}

int destinataire(message msg)
{
    return msg->destinataire;
}

BOOL estVide(message msg)
{
    return msg->vide;
}

BOOL estTransmis(message msg)
{
    return msg->transmis;
}

BOOL estRecu(message msg)
{
    return msg->recu;
}
