#include <stdio.h>
#include <stdlib.h>
#include "facility.h"

facility_t *facility_create()
{
    facility_t *facility = malloc(sizeof(facility_t));
    if(facility == NULL)
        return NULL;

    facility->area = 0;
    facility->cost = 0;
    facility->name = NULL;
    return facility;
}

void facility_free(facility_t *facility)
{
    free(facility);
}

void yesF()
{
    printf("yesF\n");
}