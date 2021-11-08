#include "book.h"

book_t* book_create()
{
    book_t *book = malloc(sizeof(book_t));
    if(book == NULL)
        return NULL;
    
    book-> name = NULL;
    book-> authors = NULL;
    book-> nAuthors = 0;
    book-> publisher = NULL;
    book-> year = 0;
    book-> isbn = 0;

    return book;
}

int book_set_name(book_t* book, char* name)
{
    book->name = realloc(book->name, sizeof(char*));
    if(book->name == NULL)
    {
        return -1;
    }
    book->name = name;
    return 0;
}

int book_set_pubYearIsbn(book_t* book, char* publisher, int year, double isbn)
{
    book->publisher = realloc(book->publisher, sizeof(char*));
    if(book->publisher == NULL)
    {
        return -1;
    }

    book->publisher = publisher;
    book->year = year;
    book->isbn = isbn;
    return 0;
}

int book_add_author(book_t *book, char *author)
{
    book->authors = realloc(book->authors, (book->nAuthors+1)*sizeof(char*));
    if(book->authors == NULL)
    {
        return -1;
    }
    book->authors[book->nAuthors] = author;
    book->nAuthors++;
    return 0;
}

void book_print(book_t book)
{   
    int i;
    printf("(\"%s\" ,(", book.name);
    for(i = 0; i < book.nAuthors; i++)
    {   
        printf("\"%s\"", book.authors[i]);
        if(i != book.nAuthors-1)
        {
            printf(", ");
        }
    }
    printf("), \"%s\", %d, %f)", book.publisher, book.year, book.isbn);
}

void book_free(book_t *book)
{
    free(book->authors);
    free(book);
}