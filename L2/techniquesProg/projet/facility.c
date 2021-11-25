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

void facility_handle_f(facility_t facility)
{
    printf("%s, %d m2, %f USD\n", facility.name, facility.area, facility.cost);
}