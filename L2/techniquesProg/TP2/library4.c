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
    int i;
    free(book->name);
    for(i = 0; i < book->nAuthors; i++)
    {
        free(book->authors[i]);
    }
    free(book->authors);
    free(book->publisher);
    free(book);
}

void library_free(library_t *library)
{
    int i;
    free(library->name);
    free(library->days);
    for(i=0; i < library->nBooks; i++)
    {
        free(library->books);
    }
    free(library);
}

int book_add_author(book_t *book, char *author)
{
    /*int i;
    if(book->nAuthors == 0)
    {
        book->authors=(char**) malloc(sizeof(char));
        book->authors[book->nAuthors]=(char*) malloc(strlen(author) * sizeof(char));
        //strcpy(book->authors[book->nAuthors], author);
        for(i = 0; i < strlen(author); i++)
        {
            book->authors[book->nAuthors][i]=author[i];
        }
    }
    else
    {
        book->authors=(char**) realloc(book->authors, book->nAuthors+1*sizeof(char));
        book->authors[book->nAuthors]=(char*) malloc(strlen(author) * sizeof(char));
        for(i = 0; i < strlen(author); i++)
        {
            book->authors[book->nAuthors][i]=author[i];
        }
    }
    book->nAuthors++;
    return 0;*/
}

int main()
{
    book_t *libro = book_create();
    library_t *libreria = library_create();

    book_add_author(libro, "Juan");

    //Error with multiple book_add
    //book_add_author(libro, "Jose Jose");
    printf("%d %s %s", libro->nAuthors, libro->authors[0], libro->authors[1]);



    book_free(libro);
    library_free(libreria);

    return 0;
}