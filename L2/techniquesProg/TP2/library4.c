#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char *name;
    char *authors;
    int nAuthors;
    char *publisher;
    int year;
    long isbn;    
} book_t;

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
    free(book);
}

void library_free(library_t *library)
{
    free(library);
}

int book_add_author(book_t *book, char *author)
{
    /*
        realloc check
        al meter un autor tenemos que meterlo a la matriz de antes, asi que se tiene que meter como matriz, no como 
        string porque si no, perdemos memoria

        authors deja memoria libre cuanod asigno sin usar strcpy, se tiene que copiar dentro del array de autores, como 
        mencionado anterior pero no asignando, sino mas bien con strcpyy

        puede ser?
    */
    book = realloc(book, sizeof(book) + sizeof(author));
    if(book == NULL)
        return -1;
    
    book-> authors = author;
    book-> nAuthors++;
    return 0;
}

/*void book_print(book_t book)
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
    printf("), \"%s\", %d, %ld)", book.publisher, book.year, book.isbn);
}

void library_print(library_t library)
{
    int i;
    printf("(\"%s\", (", library.name);
    for(i = 0; i < library.nDays; i++)
    {   
        printf("\"");
        switch(library.days[i])
        {
            case 0:
                printf("monday");
                break;
            case 1:
                printf("tuesday");
                break;
            case 2:
                printf("wednesday");
                break;
            case 3:
                printf("thursday");
                break;
            case 4:
                printf("friday");
                break;
            case 5:
                printf("saturday");
                break;
            case 6:
                printf("sunday");
                break;
            default:
                break;
        }
        printf("\"");
        if(i != library.nDays-1)
        {
            printf(", ");
        }
    }
    printf("), (");
    for(i = 0; i < library.nBooks; i++)
    {
        book_print(library.books[i]); 
    }
    printf("))\n");
}*/

int main()
{
    book_t *libro = book_create();
    library_t *libreria = library_create();

    if(book_add_author(libro, "Juan Castel") == -1)
    {
        printf("Shut");
    }
    printf("%s\n", libro->authors);
    printf("%d\n", libreria->nDays);

    book_free(libro);
    library_free(libreria);
    /*library_t sciencesLibraryt = {"Sciences Library", 
                                       {monday, tuesday, wednesday, thursday},
                                        4, 
                                        {
                                            {
                                                "The C Programming Language", 
                                                {"Brian W. Kernighan", "Dennis M. Ritchie"}, 
                                                2, 
                                                "Prentice Hall", 
                                                1988, 
                                                9780131103627
                                            },
                                            {
                                                "C: The Complete Reference",
                                                {"Herbert Schildt"},
                                                1,
                                                "McGraw-Hill Education",
                                                2000,
                                                9780072121247
                                            }
                                        }, 
                                2};

    library_t novelLibraryt = {"Novel Library", 
                                    {tuesday, wednesday, thursday, friday},
                                    4,
                                    {
                                        {
                                            "Harry Potter and the Philospher's Stone",
                                            {"J. K. Rowling"},
                                            1,
                                            "Bloomsbury",
                                            1977,
                                            9780747532699
                                        }, 
                                        {
                                            "Harry Potter and the Chamber of Secrets",
                                            {"J. K. Rowling"},
                                            1,
                                            "Bloomsbury",
                                            1988,
                                            9780747538493
                                        }
                                    },
                                    2};

    library_print(sciencesLibraryt);
    library_print(novelLibraryt);*/

    return 0;
}