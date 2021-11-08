#ifndef LIBRARY_H
#define LIBRARY_H
#include <stdlib.h>
#include <stdio.h>
#include "book.h"

typedef enum{
    monday, tuesday, wednesday, thursday, friday, saturday, sunday
} day_t;

typedef struct
{
    char *name;
    day_t *days;
    int nDays;
    book_t *books;
    int nBooks;
}library_t;

library_t* library_create();
int library_set_name(library_t*, char*);
int library_add_day(library_t*, day_t);
int library_add_book(library_t*, book_t);
void print_library(library_t*);
void library_free(library_t*);

#endif