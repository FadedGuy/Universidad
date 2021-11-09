#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

int main(int argc, char* argv[])
{
    xmlDocPtr doc;
    xmlNodePtr cur;

    if(argc != 2)
    {
        fprintf(stderr, "invalid number of arguments\n");
        return 1;
    }

    doc = xmlParseFile(argv[1]);
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

    if(!xmlStrcmp(cur->name, (const xmlChar*) "library"))
    {
        cur = cur->xmlChildrenNode;
        while(cur != NULL)
        {
            printf("%s\n", cur->name);
            cur = cur->next;
        }
    }

    xmlFreeDoc(doc);

    
    return 0;
}