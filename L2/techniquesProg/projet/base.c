#include <stdio.h>
#include <stdlib.h>
#include "base.h"

base_t *base_create()
{
    base_t *base = malloc(sizeof(base_t));
    if(base == NULL)
        return NULL;

    base->country = NULL;
    base->day = 0;
    base->facilities = NULL;
    base->month = 0;
    base->name = NULL;
    base->nfacilities = 0;
    base->year = 0;

    return base;
}

void base_free(base_t *base)
{
    free(base->facilities);
    free(base);
}

void yes()
{
    printf("yes\n");
}