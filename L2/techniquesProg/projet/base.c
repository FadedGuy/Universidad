#include <stdio.h>
#include <stdlib.h>
#include "base.h"

int base_add_facility(base_t *base, facility_t *facility)
{
    base->facilities = realloc(base->facilities, (base->nfacilities+1)*sizeof(facility_t));
    if(base->facilities == NULL)
        return 1;
    
    base->facilities[base->nfacilities] = facility;
    base->nfacilities++;
    return 0;
}

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

void base_handle_b(base_t base)
{
    printf("%s (%d-%02d-%02d, %s)\n", base.name, base.year, base.month, base.day, base.country);
}

void base_handle_c(base_t base) 
{
    printf("%s\n", base.country);
}

void base_handle_d(base_t base)
{
    printf("%d-%d-%d\n", base.year, base.month, base.day);
}

void base_handle_f(base_t base)
{
    int i;
    for(i = 0; i < base.nfacilities; i++)
    {
        facility_handle_f(*base.facilities[i]);
    }
}

void base_handle_n(base_t base)
{
    printf("%s\n", base.name);
}

void base_handle_t(base_t base)
{
    
}