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
 * Commands missing
 * 
 * fc COST: Prints the base facilities with the cost equal to COST
 * fcge COST: Prints the base facilities with the cost greater than or equal to COST
 * fcgt COST: Prints the base facilities with the cost greater than COST
 * fcle COST: Prints the base facilities with the cost less than or equal to COST
 * fclt COST: Prints the base facilities with the cost less than COST
 * fn NAME: Prints the base facilities with the name containing NAME
 * 
 ***/

/***
 * la solution doit ignorer tout noeud ou attribut qui ne décrit pas une base 
 *  constituée d’installations
 * Creer des xml different pour tester
 * 
 * if the parsing fails, or document doesn't exist, exit program with 0 or 1?, 
 *  I'd say 0 since it handles the error and gets out as expected
 * 
 * LEAKS XML
 * xmlNodeListGetString
 * xmlGetProp
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

/* 8 bytes in 1 block leak, definitely lost
NOT actually useful, directly use xmlGetProp is the same since we don't need to search
void getAttName(xmlDocPtr doc, xmlNodePtr cur, char* tag, base_t* base)
{
    while(cur != NULL)
    {
        if((!xmlStrcmp(cur->name, (const xmlChar*) tag)))
        {
            base->name = (char*)xmlGetProp(cur, (xmlChar*) "name");
        }
        cur = cur->next;
    }
}*/

void parseDate(xmlDocPtr doc, xmlNodePtr cur, base_t *base)
{
    /*
        For each xmlNodeListGetString there is a leak of 2-3 bytes in 1 bloc per each
    */
    cur = cur->xmlChildrenNode;
    while(cur != NULL)
    {
        if((!xmlStrcmp(cur->name, (const xmlChar*) "day")))
        {
            base->day = strtol((char*)xmlNodeListGetString(doc, cur->xmlChildrenNode, 1), NULL, 10);
        }
        else if((!xmlStrcmp(cur->name, (const xmlChar*) "month")))
        {
            base->month = strtol((char*)xmlNodeListGetString(doc, cur->xmlChildrenNode, 1), NULL, 10);
        }else if((!xmlStrcmp(cur->name, (const xmlChar*) "year")))
        {
            base->year = strtol((char*)xmlNodeListGetString(doc, cur->xmlChildrenNode, 1), NULL, 10);
        }
        cur = cur->next;
    }
}

void parseCountry(xmlDocPtr doc, xmlNodePtr cur, base_t *base)
{
    cur = cur->xmlChildrenNode;
    base->country = realloc(base->country, sizeof(char*));
    if(base->country == NULL)
        return;
    
    base->country = (char*) xmlNodeListGetString(doc, cur, 1);
}

void parseInFacilities(xmlDocPtr doc, xmlNodePtr cur, base_t *base)
{
    facility_t *facility = facility_create();
    if(facility == NULL)
        return;
    
    facility->name = realloc(facility->name, sizeof(char*));
    if(facility->name == NULL)
        return;

    facility->name = (char*)xmlGetProp(cur, (xmlChar*)"name");

    cur = cur->xmlChildrenNode;
    while(cur != NULL)
    {
        if((!xmlStrcmp(cur->name, (const xmlChar*) "area")))
        {
            facility->area = strtol((char*) xmlNodeListGetString(doc, cur->xmlChildrenNode, 1), NULL, 10);
        } else if((!xmlStrcmp(cur->name, (const xmlChar*) "cost")))
        {
            facility->cost = strtod((char*) xmlNodeListGetString(doc, cur->xmlChildrenNode, 1), NULL);
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
        xmlFreeDoc(doc);
        return 1;
    }

    /* Check if the root node is of type base */
    if(xmlStrcmp(cur->name, (const xmlChar*) "base"))
    {
        fprintf(stderr, "Wrong type document, root node is not \"base\"\n");
        xmlFreeDoc(doc);
        return 1; 
    }

    /* Parsed file copied to base */
    /* check null base->name if successful */
    base->name = realloc(base->name, sizeof(char*));
    if(base->name == NULL)
        return 1;

    /* 8 byte 1 bloc leak when calling xmlGetProp */
    base->name = (char*) xmlGetProp(cur, (xmlChar*)"name");

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


void menu(base_t *base)
{
    char choice[BUFFER];
    char* command;
    char* param; 

    printf("BM> ");
    fgets(choice, BUFFER, stdin);
    choice[strlen(choice)-1] = '\0';

    /* Separate choice into command and parameter (if entered)*/
    command = NULL;
    param = strstr(choice, " ");
    if(param != NULL)
    {
        param = param+1;
        command = choice;
        command[strlen(choice)-strlen(param)-1] = '\0';
        printf("%ld", strlen(param));
    }
    else
    {
        command = choice;
    }

    printf("\t\t%s <--- command:%sparam:%s\n", choice, command, param);

    if(strlen(choice) > 18)
    {
        fprintf(stderr, "Too many characters for the command\n");
    } else if(strcmp(choice, "h") == 0)
    {
        help_command();
    } else if(strcmp(choice, "b") == 0)
    {
        base_handle_b(*base);
    } else if(strcmp(choice, "c") == 0)
    {
        base_handle_c(*base);
    } else if(strcmp(choice, "d") == 0)
    {
        base_handle_d(*base);
    } else if(strcmp(choice, "t") == 0)
    {
        base_handle_t(*base);
    } else if(strcmp(choice, "f") == 0)
    {
        base_handle_f(*base);
    } /*else if(strcmp(ch, "fc") == 0)
    {
        double cost = 0;
        if(paramExist == 1 && ((cost = strtod(choice+espace, NULL)) != 0 || (choice[espace+1] == '0' && choice[strlen(choice)-1] == '0')))
        {
            printf("valid param %f\n", cost);
        }
        else
        {
            printf("non valid param\n");
        }
    }*/ else if(strcmp(choice, "n") == 0)
    {
        base_handle_n(*base);
    } else if(strcmp(choice, "v") == 0)
    {
        printf("BM (Base Manager) 20211123\n\nCopyright (C) 2021 Aceves Kevin and Genthon Baptiste.\n\nWritten by Kevin Aceves <kevin.aceves-siordia@etud.univ-pau.fr> and Genthon Baptiste <baptiste.genthon@etud.univ-pau.fr>.\n");
    } else if(strcmp(choice, "b") == 0)
    {
        base_handle_b(*base);
    } else if(strcmp(choice, "q") == 0)
    {
        printf("Goodbye !\n");
        return;
    } 
    else 
    {
        fprintf(stderr, "Invalid command\n");
    } 
    
    menu(base);
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
        fprintf(stderr, "Unable to parse\n");
        return 1;
    }
    
    menu(base);
    /*printf("%s\n", base->name);
    printf("%d %d %d\n", base->day, base->month, base->year);
    printf("%s\n", base->country);
    printf("%s\n", base->facilities[0]->name);*/
    
    base_free(base);
    return 0;
}