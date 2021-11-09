#include "library.h"

char *days_str[] = {"monday", "tuesday", "wednesday", "thursday", "saturday", "sunday"};
static int library_nLibraries = 0;

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
    library_nLibraries++;
    
    return library;
}

int library_set_name(library_t *library, char* name)
{
    library->name = realloc(library->name, sizeof(char*));
    if(library->name == NULL)
    {
        return -1;
    }

    library->name = name;
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

void print_library(library_t* library)
{
    int i;
    printf("(\"%s\", (", library->name);
    for(i = 0; i < library->nDays; i++)
    {
        printf("\"%s\",", days_str[library->days[i]]);
        if(i != library->nDays-1)
            printf(", ");
    }
    printf("), (");
    for(i = 0; i < library->nBooks; i++)
    {
        book_print(library->books[i]);
    }
    printf("))\n");
}

void library_free(library_t *library)
{
    library_nLibraries--;
    free(library->days);
    free(library->books);
    free(library);
}

int library_count()
{
    return library_nLibraries;
}