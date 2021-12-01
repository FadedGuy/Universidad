#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#include "base.h"
#include "facility.h"

#define BUFFER 20

/***
 * http://xmlsoft.org/ Documentation
 * http://xmlsoft.org/tutorial/xmltutorial.pdf Guide tutorial
 ***/

/***
 * Créer des xml differents pour tester
 * 
 * if the parsing fails, or document doesn't exist, exit program with 0 or 1?, 
 *  I'd say 0 since it handles the error and gets out as expected
 * 
 * when using a xmlChar* as a string, dont free the memory right away since we are using it for the 
 * variable as a pointer, free at the end in base_free and facility_free
 * If used to convert to double or long it NEEDS to be freed right after it's used.
 ***/

void help_command()
{
    printf("b: Prints the base\n");
    printf("c: Prints the base country\n");
    printf("d: Prints the base date\n");
    printf("f: Prints the base facilities\n");
    printf("fc COST: Prints the base facilities with the cost equal to COST\n");
    printf("fcge COST: Prints the base facilities with the cost greater than or equal to COST\n");
    printf("fcgt COST: Prints the base facilities with the cost greater than COST\n");
    printf("fcle COST: Prints the base facilities with the cost less than or equal to COST\n");
    printf("fclt COST: Prints the base facilities with the cost less than COST\n");
    printf("fn NAME: Prints the base facilities with the name containing NAME\n");
    printf("h: Prints this help\n");
    printf("n: Prints the base name\n");
    printf("t: Prints the base total cost\n");
    printf("v: Prints the BM version\n");
    printf("q: Quits BM \n");
}

void parseDate(xmlDocPtr doc, xmlNodePtr cur, base_t *base)
{
    xmlChar* key;
    cur = cur->xmlChildrenNode;
    while(cur != NULL)
    {
        if((!xmlStrcmp(cur->name, (const xmlChar*) "day")))
        {
            key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
            base->day = strtol((char*)key, NULL, 10);
            xmlFree(key);
        }
        else if((!xmlStrcmp(cur->name, (const xmlChar*) "month")))
        {
            key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
            base->month = strtol((char*)key, NULL, 10);
            xmlFree(key);
        }else if((!xmlStrcmp(cur->name, (const xmlChar*) "year")))
        {
            key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
            base->year = strtol((char*)key, NULL, 10);
            xmlFree(key);
        }
        cur = cur->next;
    }
}

void parseCountry(xmlDocPtr doc, xmlNodePtr cur, base_t *base)
{
    xmlChar* key;
    cur = cur->xmlChildrenNode;
    
    /* Refer to comment on xmlChar* use on char* */
    key = xmlNodeListGetString(doc, cur, 1);
    base->country = (char*) key;
}

void parseInFacilities(xmlDocPtr doc, xmlNodePtr cur, base_t *base)
{
    xmlChar* key;
    facility_t *facility = facility_create();
    if(facility == NULL)
        return;

    key = xmlGetProp(cur, (const xmlChar*) "name");
    facility->name = (char*)key;

    cur = cur->xmlChildrenNode;
    while(cur != NULL)
    {
        if((!xmlStrcmp(cur->name, (const xmlChar*) "area")))
        {
            key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
            facility->area = strtol((char*) key, NULL, 10);
            xmlFree(key);
        } else if((!xmlStrcmp(cur->name, (const xmlChar*) "cost")))
        {
            key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
            facility->cost = strtod((char*) key, NULL);
            xmlFree(key);
        }
        cur = cur->next;
    }
    
    if(base_add_facility(base, facility) != 0)
    {
        facility_free(facility);    
        return;
    }
}

void parseFacilities(xmlDocPtr doc, xmlNodePtr cur, base_t *base)
{
    cur = cur->xmlChildrenNode;
    while(cur != NULL)
    {   
        if((!xmlStrcmp(cur->name, (const xmlChar*) "facility")))
        {
            parseInFacilities(doc, cur, base);
        }
        cur = cur->next;
    }
}

int parseDoc(char *filename, base_t* base)
{
    xmlDocPtr doc;
    xmlNodePtr cur;
    xmlChar* key;

    doc = xmlParseFile(filename);
    /* Check if parse was successful */
    if(doc == NULL)
    {
        fprintf(stderr, "Unable to parse the document\n");
        return 1;
    }

    cur = xmlDocGetRootElement(doc);
    /* Check if there is a root element, meaning it's not an empty document */
    if(cur == NULL)
    {
        fprintf(stderr, "Empty file\n");
        xmlCleanupParser();
        xmlFreeDoc(doc);
        return 1;
    }

    /* Check if the root node is of type base */
    if(xmlStrcmp(cur->name, (const xmlChar*) "base"))
    {
        fprintf(stderr, "Wrong type document, root node is not \"base\"\n");
        xmlCleanupParser();
        xmlFreeDoc(doc);
        return 1; 
    }

    /* File to base_t */
    key = xmlGetProp(cur, (xmlChar*)"name");
    base->name = (char*) key;

    cur = cur->xmlChildrenNode;
    while(cur != NULL)
    {
        if((!xmlStrcmp(cur->name, (const xmlChar*) "date")))
        {
            parseDate(doc, cur, base);
        }else if((!xmlStrcmp(cur->name, (const xmlChar*) "country")))
        {
            parseCountry(doc, cur, base);
        }
        else if((!xmlStrcmp(cur->name, (const xmlChar*) "facilities")))
        {
            parseFacilities(doc, cur, base);
        }
        cur = cur->next;
    }

    xmlCleanupParser();
    xmlFreeDoc(doc);
    return 0;
}

/* Verifies param is right for the command */
int verifParamNumberCommand(char *command, char* param)
{
    int i;
    if(!strcmp(param, ""))
    {
        printf("Missing parameter for the %s command\n", command);
        return 0;
    } 
    else {
        for(i = 0; i < strlen(param); i++)
        {
            /* 
                Allowed point(.) but may create problems. 
                Maybe allow only one point? 
            */
            if(!((param[i] >= '0' && param[i] <= '9') || param[i] == '.'))
            {
                printf("Invalid parameter for the %s command\n", command);
                return 0;
            }
        }
    }
    

    return 1;
}

void menu(base_t *base)
{
    char choice[BUFFER];
    char* command;
    char* param; 
    int c; 
    int lenChoice;

    /* 
        Since we use return when q command is found, no need to make any condition
        hence, infinite loop. Unless return
        Accepts q(espace) but not q(espace)(espace) since the ladder is not null on param
    */
    while(1)
    {
        printf("BM> ");
        fgets(choice, BUFFER, stdin);
        lenChoice = strlen(choice);
        /*
            A little trick since the left-most condition is evaluated first, we only flush        
            if the length of choice is greater than 18, meaning there's leftover in stdin 
        */
        while(strlen(choice) > 18 && (c = getchar()) != '\n' && c != EOF);

        /* 
            Separate choice into command and parameter (if entered), null if not
            might need to remove whitespace trail(but then would\nt be able to search for only spaces)
        */
        choice[strlen(choice)-1] = '\0';
        command = NULL;
        param = strstr(choice, " ");
        if(param != NULL)
        {
            param = param+1;
            command = choice;
            command[strlen(choice)-strlen(param)-1] = '\0';
        }
        else
        {
            param = "";
            command = choice;
        }

        if(lenChoice > 18)
        {
            fprintf(stderr, "Too many characters for the command\n");
        }
        else if(!strcmp(command, "b") && !strcmp(param, ""))
        {
            base_handle_b(*base);
        }
        else if(!strcmp(command, "c") && !strcmp(param, ""))
        {
            base_handle_c(*base);
        }
        else if(!strcmp(command, "d") && !strcmp(param, ""))
        {
            base_handle_d(*base);
        }
        else if(!strcmp(command, "f") && !strcmp(param, ""))
        {
            base_handle_f(*base);
        }
        else if(!strcmp(command, "fc"))
        {
            if (verifParamNumberCommand(command, param))
            {
                base_handle_fc(*base, strtod(param, NULL));
            }
        }
        else if(!strcmp(command, "fcge"))
        {
            if (verifParamNumberCommand(command, param))
            {
                base_handle_fcge(*base, strtod(param, NULL));
            }
        }
        else if(!strcmp(command, "fcgt"))
        {
            if (verifParamNumberCommand(command, param))
            {
                base_handle_fcgt(*base, strtod(param, NULL));
            }
        }
        else if(!strcmp(command, "fcle"))
        {
            if (verifParamNumberCommand(command, param))
            {
                base_handle_fcle(*base, strtod(param, NULL));
            }
        }
        else if(!strcmp(command, "fclt"))
        {
            if (verifParamNumberCommand(command, param))
            {
                base_handle_fclt(*base, strtod(param, NULL));
            }
        }
        else if(!strcmp(command, "fn"))
        {
            if(!strcmp(param, ""))
            {
                printf("Missing parameter for the fn command\n");
            }
            else
            {
                base_handle_fn(*base, param);
            }
        }
        else if(!strcmp(command, "h") && !strcmp(param, ""))
        {
            help_command();
        }
        else if(!strcmp(command, "n") && !strcmp(param, ""))
        {
            base_handle_n(*base);
        }
        else if(!strcmp(command, "t") && !strcmp(param, ""))
        {
            base_handle_t(*base);
        }
        else if(!strcmp(command, "v") && !strcmp(param, ""))
        {
            printf("BM (Base Manager) 20211127\n\nCopyright (C) 2021 Aceves Kevin and Genthon Baptiste.\n\nWritten by Kevin Aceves <kevin.aceves-siordia@etud.univ-pau.fr> and Genthon Baptiste <baptiste.genthon@etud.univ-pau.fr>.\n");
        }
        else if(!strcmp(command, "q") && !strcmp(param, ""))
        {
            return;
        }
        else
        {
            fprintf(stderr, "Invalid command\n");
        }
    }
    
}

int main(int argc, char *argv[])
{
    base_t *base = base_create();

    if(argc != 2)
    {
        fprintf(stderr, "Invalid number of arguments\n");
        return 1;
    }

    if(parseDoc(argv[1], base) != 0)
    {
        return 1;
    }
    
    menu(base);
    printf("Goodbye !\n");
    
    base_free(base);
    return 0;
}
