#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char *name;
    char **authors;
    int nAuthors;
    char *publisher;
    int year;
    double isbn;    
} book_t;

char *days_str[] = {"monday", "tuesday", "wednesday", "thursday", "saturday", "sunday"};

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

library_t* library_create()
{
    library_t *library = malloc(sizeof(library_t));
    if(library == NULL)
        return NULL;
    
    library-> name = NULL;
    library-> days = NULL;
    library-> nDays = 0;
    library-> books = NULL;
    library-> nBooks = 0;
    
    return library;
}

void book_free(book_t *book)
{
    free(book->authors);
    free(book);
}

void library_free(library_t *library)
{
    free(library->days);
    free(library->books);
    free(library);
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

int library_add_day(library_t *library, day_t day)
{
    library->days = realloc(library->days, (library->nDays+1)*sizeof(day_t));
    if(library->days == NULL)
    {
        return -1;
    }
    library->days[library->nDays] = day;
    library->nDays++;
    return 0;
}

int library_add_book(library_t *library, book_t book)
{
    library->books = realloc(library->books, (library->nBooks+1)*sizeof(book_t));
    if(library->books == NULL)
    {
        return -1;
    }
    library->books[library->nBooks] = book;
    library->nBooks++;
    return 0;
}

int main()
{
    book_t *libro = book_create();
    library_t *libreria = library_create();

    book_add_author(libro, "Juan");
    book_add_author(libro, "Jose Jose");

    library_add_day(libreria, tuesday);
    library_add_book(libreria, (*libro));

    /* Tests 
    printf("Author 1: %s\n", libro->authors[0]);
    printf("Author 2: %s\n", libro->authors[1]);
    printf("Day open: %s\n", days_str[libreria->days[0]]);
    printf("Author 1 book 1: %s\n", libreria->books[0].authors[0]);
    */

    book_free(libro);
    library_free(libreria);

    return 0;
}