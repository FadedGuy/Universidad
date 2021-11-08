#ifndef BOOK_H
#define BOOK_H
#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    char *name;
    char **authors;
    int nAuthors;
    char *publisher;
    int year;
    double isbn;    
} book_t;

book_t* book_create();
int book_set_name(book_t*, char*);
int book_set_pubYearIsbn(book_t*, char*, int, double);
int book_add_author(book_t*, char*);
void book_print(book_t book);
void book_free(book_t*);

#endif
