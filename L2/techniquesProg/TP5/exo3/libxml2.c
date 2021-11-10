#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

/*
    xmlCleanupParser
    xmlDocGetRootElement
    xmlFreeDoc
    xmlGetProp
    xmlNodeListGetString
    xmlParseFile
    xmlStrcmp
*/

void getReferenceLibrary(xmlDocPtr doc, xmlNodePtr cur){
    xmlChar *uri;
    while(cur != NULL){
        if((!xmlStrcmp(cur->name, (const xmlChar*) "library"))){
            uri = xmlGetProp(cur, (const xmlChar*) "name");
            printf("\tname: %s\n", uri);
            xmlFree(uri);
        }
        cur = cur->next;
    }
}

void parseDays(xmlDocPtr doc, xmlNodePtr cur){
    xmlChar *key;
    cur = cur->xmlChildrenNode;
    while(cur != NULL){
        if((!xmlStrcmp(cur->name, (const xmlChar*) "day"))){
            key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
            printf("\t\tday: %s\n", key);
            xmlFree(key);
        }
        cur = cur->next;
    }
}

void parseInAuthors(xmlDocPtr doc, xmlNodePtr cur){
    xmlChar *key;
    cur = cur->xmlChildrenNode;
    while(cur != NULL){
        if((!xmlStrcmp(cur->name, (const xmlChar*) "author"))){
            key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
            printf("\t\t\t\tauthor: %s\n", key);
            xmlFree(key);
        } 
        cur = cur->next;
    }    
}

void parseInBooks(xmlDocPtr doc, xmlNodePtr cur){
    xmlChar *key;
    cur = cur->xmlChildrenNode;
    while(cur != NULL){
        if((!xmlStrcmp(cur->name, (const xmlChar*) "authors"))){
            printf("\t\t\tauthors: %s\n", key);
            parseInAuthors(doc, cur);
        } 
        else if((!xmlStrcmp(cur->name, (const xmlChar*) "publisher"))){
            key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
            printf("\t\t\tpublisher: %s\n", key);
            xmlFree(key);
        }
        else if((!xmlStrcmp(cur->name, (const xmlChar*) "year"))){
            key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
            printf("\t\t\tyear: %s\n", key);
            xmlFree(key);
        }
        else if((!xmlStrcmp(cur->name, (const xmlChar*) "isbn"))){
            key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
            printf("\t\t\tisbn: %s\n", key);
            xmlFree(key);
        }

        cur = cur->next;
    }    
}

void parseBooks(xmlDocPtr doc, xmlNodePtr cur){
    cur = cur->xmlChildrenNode;
    while(cur != NULL){
        if((!xmlStrcmp(cur->name, (const xmlChar*) "book"))){
            printf("\t\tbook:\n");
            parseInBooks(doc, cur);
        }
        cur = cur->next;
    }    
}


int parseDoc(char* filename)
{
    xmlDocPtr doc; /* Has document */ 
    xmlNodePtr cur; /* Individual interactable nodes (list) */

    doc = xmlParseFile(filename);
    if(doc == NULL) 
    {
        fprintf(stderr, "unable to parse the document\n");
        return 1;
    }

    cur = xmlDocGetRootElement(doc);
    if(cur == NULL)
    {
        fprintf(stderr, "empty document\n");
        xmlFreeDoc(doc);
        return 1;
    }

    /* Change library to the root keyword to make sure xml is the right type */
    if(xmlStrcmp(cur->name, (const xmlChar*) "library")){
        xmlFreeDoc(doc);
        return 0;
    }
    
    printf("library:\n");
    /* Get library name by attribute */
    getReferenceLibrary(doc, cur);

    cur = cur->xmlChildrenNode;
    while(cur != NULL)
    {
        /* Here we are iterating through the list until the end
            Multiple ifs would serve to check what type of keyword we need and 
            properly handle it
         */ 
        if((!xmlStrcmp(cur->name, (const xmlChar*) "days")))
        {
            printf("\tdays:\n");
            parseDays(doc, cur);
        }
        else if((!xmlStrcmp(cur->name, (const xmlChar*) "books"))){
            printf("\tbooks:\n");
            parseBooks(doc, cur);
        }
        cur = cur->next;
    }

    xmlFreeDoc(doc);
    return 0;
}

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        fprintf(stderr, "invalid number of arguments\n");
        return 1;
    }
    
    return parseDoc(argv[1]);
}