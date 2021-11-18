#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#include "base.h"
#include "facility.h"
/***
 * http://xmlsoft.org/ Documentation
 * http://xmlsoft.org/tutorial/xmltutorial.pdf Guide tutorial
 ***/

/***
 * Commands h
 * b: Prints the base
 * c: Prints the base country
 * d: Prints the base date
 * f: Prints the base facilities
 * 
 * fc COST: Prints the base facilities with the cost equal to COST
 * fcge COST: Prints the base facilities with the cost greater than or equal to COST
 * fcgt COST: Prints the base facilities with the cost greater than COST
 * fcle COST: Prints the base facilities with the cost less than or equal to COST
 * fclt COST: Prints the base facilities with the cost less than COST
 * fn NAME: Prints the base facilities with the name containing NAME
 * 
 * h: Prints this help
 * n: Prints the base name
 * t: Prints the base total cost
 * v: Prints the BM version
 * q: Quits BM 
 ***/

/***
 * la solution doit ignorer tout noeud ou attribut qui ne décrit pas une base 
 *  constituée d’installations
 * Creer des xml different pour tester
 * 
 * if the parsing fails, or document doesn't exist, exit program with 0 or 1?, 
 *  I'd say 0 since it handles the error and gets out as expected
 * Convert from xmlChar to char
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

void getBaseName(xmlDocPtr doc, xmlNodePtr cur, base_t *base){
    xmlChar *uri;
    while(cur != NULL){
        if((!xmlStrcmp(cur->name, (const xmlChar*) "base"))){
            uri = xmlGetProp(cur, (const xmlChar*) "name");

            base->name = malloc(sizeof(char*));
            if(base->name == NULL)
                return;
            base->name = (char*)uri;
            printf("name: %s\n", base->name);
            /* Prints right inside function */ 
            xmlFree(uri); /* xmlFree not in functions authorized */
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
    if(xmlStrcmp(cur->name, (const xmlChar*) "base")){
        fprintf(stderr, "Wrong type document, root node is not \"base\"\n");
        xmlFreeDoc(doc);
        return 1; 
    }

    /* Parsed file copied to base*/
    getBaseName(doc, cur, base);
    printf("%s\n", base->name);
    /*xmlCleanupParser();*/
    xmlFreeDoc(doc);
    return 0;
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

    printf("%s\n", base->name);
    base_free(base);
    return 0;
}