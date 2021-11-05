#include <stdio.h>
#include "message.h"

int main()
{
    srand(time(NULL));
    BOOL success = TRUE;
    char* txt = "Salut robot";
    int dest = rand();

    /* Creer */
    message msg = creer();
    if(msg == NULL)
        success = FALSE;

    if(success == FALSE)
    {
        fprintf(stderr, "Implementation incorrect du creer()\n");
        exit(EXIT_FAILURE);
    }

    /* Editer */
    success = TRUE;
    if(estVide(msg))
    {
        msg = editer(msg, txt);
        if(strcmp(msg->msg, txt) != 0)
            success = FALSE;
    } else {
        fprintf(stderr, "Implementation incorrect du creer()\n");
        exit(EXIT_FAILURE);        
    }

    if(success == FALSE)
    {
        fprintf(stderr, "Implementation incorrect du editer()\n");
        exit(EXIT_FAILURE);
    }

    /* Envoyer */ 
    success = TRUE;
    if(!estVide(msg))
    {
        msg = envoyer(msg, dest);
        msg->recu = TRUE;
        if(msg->destinataire != dest)
            success = FALSE;
    } else {
        fprintf(stderr, "Implementation incorrect du editer()\n");
        exit(EXIT_FAILURE);
    }

    if(success == FALSE)
    {
        fprintf(stderr, "Implementation incorrect du envoyer()\n");
        exit(EXIT_FAILURE);
    }

    success = TRUE;
    if(msg->destinataire != accuserReception(msg)->destinataire || 
        msg->id != accuserReception(msg)->id ||
        strcmp(msg->msg, accuserReception(msg)->msg) != 0)
        {
            success = FALSE;
        }

    if(success == FALSE){
        fprintf(stderr, "Implementation incorrect du editer()\n");
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "Implementation correct");

    return 0;
}